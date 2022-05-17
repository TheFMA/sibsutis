#include <cpu.hpp>
#include <interface.hpp>

int CPU::getCommand(){
    return this->command;
}

int CPU::getOperand(){
    return this->operand;
}

int CPU::getCurrentMemory(){
    return this->currentMemory;
}

void CPU::setCurrentMemory(int value, Memory& memory){
    int data;
    memory.get(value, data);
    commandDecode(command, operand, data);
    this->currentMemory = value;
}

void CPU::stepCurrentMemory(Memory& memory){
    int tmp = getCurrentMemory();
    setCurrentMemory(++tmp, memory);
}

int CPU::getAccumulator(){
    return this->accumulator;
}

void CPU::setAccumulator(int value){
    this->accumulator = value;
}

int CPU::fromDirectToAdditional(int a){
    if(a & (1 << 13)){
        a = ~a;
        a &= 0b1111111111111;
        a |= (1 << 13);
        a += 1;
    }
    return a;
}

int CPU::fromAdditionalToDirect(int a){
    if(a & (1 << 13)){
        a -= 1;
        a = ~a;
        a &= 0b1111111111111;
        a |= (1 << 13);
    }
    a |= (1 << 14);
    return a;
}

int CPU::ALU(int oper, int a, int b, Memory& memory){
    int result = 0;
    a -= 1 << 14;
    b -= 1 << 14;
    int signA = a & (1 << 13);
    int signB = b & (1 << 13);
    switch (oper){
    case OPER_PLUS:
        a = fromDirectToAdditional(a);
        b = fromDirectToAdditional(b);
        result = a + b;
        if(signA == signB){
            if(signA != (result & (1 << 13))){
                memory.reg.set(REG_OVERFLOW, true);
            }
        }
        result = fromAdditionalToDirect(result);
        break;
    case OPER_MINUS:
        a = fromDirectToAdditional(a);
        b = fromDirectToAdditional(b);
        result = a - b;
        if(result < 0){
            result = (1 << 15) + result;
        }
        if(signA != signB){
            if(signA != (result & (1 << 13))){
                memory.reg.set(REG_OVERFLOW, true);
            }
        }
        result = fromAdditionalToDirect(result);
        break;
    case OPER_MULTI:
        a &= ~(1 << 13);
        b &= ~(1 << 13);
        result = a * b;
        if(a * b >= 8192){
            memory.reg.set(REG_OVERFLOW, true);
        }
        result %= (1 << 14);
        if(signA ^ signB){
            result |= 1 << 13;
        }
        break;
    case OPER_DIVISION:
        if(b == 0){
            memory.reg.set(REG_DEVISION_BY_ZERO, true);
            break;
        }
        a &= ~(1 << 13);
        b &= ~(1 << 13);
        result = a / b;
        if(signA ^ signB){
            result |= 1 << 13;
        }
        break;
    }
    if(result == 0x2000){
        result &= ~(1 << 13);
    }
    setAccumulator(result | (1 << 14));
    
    return 0;
}

int CPU::CU(Memory& memory, Console console, bool& isDrawing){
    int tmp, tmp1, tmp2;
    bool tmpFlag;
    switch(command){
    case READ:
        isDrawing = false;
        tmp = console.input();
        if(tmp > 8191 || tmp < -8190){
            memory.reg.set(REG_OVERFLOW, true);
        }
        if(tmp < 0){
            tmp |= 1 << 13;
        }
        tmp &= 0b11111111111111;
        tmp |= 1 << 14;
        tmp = fromAdditionalToDirect(tmp);
        memory.set(operand, tmp);
        stepCurrentMemory(memory);
        isDrawing = true;
        break;
    case WRITE:
        memory.get(operand, tmp);
        tmp &= ~(1 << 14);
        if(tmp & (1 << 13)){
            tmp &= ~(1 << 13);
            tmp = -tmp;
        }
        
        console.output(tmp);
        stepCurrentMemory(memory);
        break;
    case LOAD:
        memory.get(operand, accumulator);
        stepCurrentMemory(memory);
        break;
    case STORE:
        memory.set(operand, accumulator);
        stepCurrentMemory(memory);
        break;
    case ADD:
        memory.get(operand, tmp);
        ALU(OPER_PLUS, accumulator, tmp, memory);
        stepCurrentMemory(memory);
        break;
    case SUB:
        memory.get(operand, tmp);
        ALU(OPER_MINUS, accumulator, tmp, memory);
        stepCurrentMemory(memory);
        break;
    case DIVIDE:
        memory.get(operand, tmp);
        ALU(OPER_DIVISION, accumulator, tmp, memory);
        stepCurrentMemory(memory);
        break;
    case MUL:
        memory.get(operand, tmp);
        ALU(OPER_MULTI, accumulator, tmp, memory);
        stepCurrentMemory(memory);
        break;
    case JUMP:
        if(operand > 100){
            memory.reg.set(REG_OUT_OF_MEMORY_RANGE, true);
            break;
        }
        setCurrentMemory(operand, memory);
        break;
    case JNEG:
        if(accumulator & (1 << 13)){
            if(operand > 100){
                memory.reg.set(REG_OUT_OF_MEMORY_RANGE, true);
                break;
            }
            setCurrentMemory(operand, memory);
            break;
        }
        stepCurrentMemory(memory);
        break;
    case JZ:
        if(accumulator == (1 << 14)){
            if(operand > 100){
                memory.reg.set(REG_OUT_OF_MEMORY_RANGE, true);
                break;
            }
            setCurrentMemory(operand, memory);
            break;
        }
        stepCurrentMemory(memory);
        break;
    case HALT:
        memory.reg.set(REG_IGNORE_TACTS, true);
        break;
    case NOT:
        tmp = ~accumulator & 0b111111111111111;
        memory.set(operand, tmp);
        stepCurrentMemory(memory);
        break;
    case AND:
        memory.get(operand, tmp);
        accumulator &= tmp;
        stepCurrentMemory(memory);
        break;
    case OR:
        memory.get(operand, tmp);
        accumulator |= tmp;
        stepCurrentMemory(memory);
        break;
    case XOR:
        memory.get(operand, tmp);
        accumulator ^= tmp;
        stepCurrentMemory(memory);
        break;
    case JNS:
        if((accumulator & (1 << 13)) == 0){
            if(operand > 100){
                memory.reg.set(REG_OUT_OF_MEMORY_RANGE, true);
                break;
            }
            setCurrentMemory(operand, memory);
            break;
        }
        stepCurrentMemory(memory);
        break;
    case JC:
        memory.reg.get(REG_OVERFLOW, tmpFlag);
        if(tmpFlag){
            if(operand > 100){
                memory.reg.set(REG_OUT_OF_MEMORY_RANGE, true);
                break;
            }
            setCurrentMemory(operand, memory);
            break;
        }
        stepCurrentMemory(memory);
        break;
    case JNC:
        memory.reg.get(REG_OVERFLOW, tmpFlag);
        if(!tmpFlag){
            if(operand > 100){
                memory.reg.set(REG_OUT_OF_MEMORY_RANGE, true);
                break;
            }
            setCurrentMemory(operand, memory);
            break;
        }
        stepCurrentMemory(memory);
        break;
    case JP:
        if(accumulator & 1){
            if(operand > 100){
                memory.reg.set(REG_OUT_OF_MEMORY_RANGE, true);
                break;
            }
            setCurrentMemory(operand, memory);
            break;
        }
        stepCurrentMemory(memory);
        break;
    case JNP:
        if(accumulator & 1 == 0){
            if(operand > 100){
                memory.reg.set(REG_OUT_OF_MEMORY_RANGE, true);
                break;
            }
            setCurrentMemory(operand, memory);
            break;
        }
        stepCurrentMemory(memory);
        break;
    case CHL:
        memory.get(operand, tmp);
        accumulator = tmp << 1;
        stepCurrentMemory(memory);
        break;
    case SHR:
        memory.get(operand, tmp);
        accumulator = tmp >> 1;
        stepCurrentMemory(memory);
        break;
    case RCL:
        memory.get(operand, tmp);
        accumulator = (tmp << 1) | (tmp >> 14);
        stepCurrentMemory(memory);
        break;
    case RCR:
        memory.get(operand, tmp);
        accumulator = (tmp >> 1) | (tmp << 14);
        stepCurrentMemory(memory);
        break;
    case NEG:
        memory.get(operand, tmp);
        accumulator = fromDirectToAdditional(accumulator);
        stepCurrentMemory(memory);
        break;
    case ADDC:
        memory.get(operand, tmp);
        memory.get(accumulator, tmp1);
        ALU(OPER_PLUS, tmp, tmp1, memory);
        stepCurrentMemory(memory);
        break;
    case SUBC:
        memory.get(operand, tmp);
        memory.get(accumulator, tmp1);
        ALU(OPER_MINUS, tmp, tmp1, memory);
        stepCurrentMemory(memory);
        break;
    case LOGLC:
        memory.get(operand, tmp);
        accumulator = tmp << accumulator;
        stepCurrentMemory(memory);
        break;
    case LOGRC:
        memory.get(operand, tmp);
        accumulator = tmp >> accumulator;
        stepCurrentMemory(memory);
        break;
    case RCCL:
        memory.get(operand, tmp);
        accumulator = tmp << accumulator | tmp >> (15 - accumulator);
        stepCurrentMemory(memory);
        break;
    case RCCR:
        memory.get(operand, tmp);
        accumulator = tmp >> accumulator | tmp << (15 - accumulator);
        stepCurrentMemory(memory);
        break;
    case MOVA:
        memory.get(operand, tmp);
        memory.set(accumulator, tmp);
        stepCurrentMemory(memory);
        break;
    case MOVR:
        memory.get(accumulator, tmp);
        memory.set(operand, tmp);
        stepCurrentMemory(memory);
        break;
    case MOVCA:
        memory.get(operand, tmp);
        memory.get(accumulator, tmp1);
        memory.set(tmp1, tmp);
        stepCurrentMemory(memory);
        break;
    case MOVCR:
        memory.get(accumulator, tmp);
        memory.get(tmp, tmp1);
        memory.set(operand, tmp1);
        stepCurrentMemory(memory);
        break;
    }
    
    return 0;
}

int CPU::commandEncode(int command, int operand, int &value) {
    if(command >= 128 || operand >= 128){
        return -1;
    }
    value = 0;
    value = (command << 7) | operand;
    return 0;
}

int CPU::commandDecode(int& command, int& operand, int value) {
    if(value >= 1 << 14){
        command = 0;
        operand = 0;
        return -1;
    }
    operand = value & 0b00000001111111;
    command = (value & 0b11111110000000) >> 7;
    return 0;
}