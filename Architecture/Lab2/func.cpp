#include "mySimpleComputer.h"
//инициализирует оперативную память Simple Computer, задавая всем еѐ ячейкам нулевые значения.
int sc_memoryInit()
{
    memset(simplememory, 0, 100);
    return 0;
}
//задает значение указанной ячейки памяти как value
int sc_memorySet(int address, int value)
{
    if (address > (memory - 1) && address < 0)
    {
        return OUT_OF_MEMORY;
    }
    else
    {
        simplememory[address] = value;
        return 0;
    }
}
//возвращает значение указанной ячейки памяти в value
int sc_memoryGet(int address, int *value)
{
    if (address > (memory - 1) && address < 0)
    {
        return OUT_OF_MEMORY;
    }
    else
    {
        *value = simplememory[address];
        return 0;
    }
}
//сохраняет содержимое памяти в файл в бинарном виде
int sc_memorySave(char *filename)
{
    FILE *output;
    output = fopen(filename, "wb");
    fwrite(simplememory, sizeof(int), 100, output);
    fclose(output);
    return 0;
}
//загружает из указанного файла содержимое оперативной памяти
int sc_memoryLoad(char *filename)
{
    FILE *output;
    output = fopen(filename, "rb");
    fread(simplememory, sizeof(int), 100, output);
    fclose(output);
    return 0;
}
//–инициализирует регистр флагов нулевым значением;
int sc_regInit(void)
{
    flag = 0;
    return 0;
}
//устанавливает значение указанного регистра флагов.
// ―Flags‖ – состояние регистра флагов («П» - переполнение при выполнении операции,
// s «М» - ошибка выхода за границы памяти, «Т» - игнорирование
// тактовых импульсов, «Е» - указана неверная команда);

int sc_regSet(int register1, int value)
{
    if (register1 < 0 && register1 > 4 && value != 1 && value != 0)
    {
        return -1;
    }

    else if (value == 1)
    {
        IN_EDINUA(flag, register1);
    }

    else if (value == 0)

        IN_NULL(flag, register1);
    return 0;
}
//возвращает значение указанного флага
int sc_regGet(int register1, int *value)
{
    if (register1 < 0 && register1 > 4)
    {
        return -1;
    }
    else
    {
        *value = GET_VALUE(flag, register1);
        return 0;
    }
}
//кодирует команду с указанным номером и операндом и помещает результат в value
int sc_commandEncode(int command, int operand, int *value)
{
    if (command < 0x10 || (command > 0x11 && command < 0x20) || (command > 0x21 && command < 0x30) ||
        (command > 0x33 && command < 0x40) || (command > 0x43 && command < 0x51) || command > 0x76)
    {
        return -1;
    }
    // В переменную по адресу (value) заносим первые 7 бит - операнд
    *value = operand;
    // Затем вносим операцию, предварительно сдвинув ее на 7 бит влево.
    *value |= command << 7;
    return 0;
}
//декодирует значение как команду Simple Computer. Если декодирование невозможно, то устанавливается флаг Е
// «указана неверная команда», и функция завершается с ошибкой.
int sc_commandDecode(int value, int *command, int *operand)
{
    int commandd, operandd;
    operandd = value & 0x7F;
    commandd = (value >> 7) & 0x7F;
    if (commandd < 0x10 || (commandd > 0x11 && commandd < 0x20) || (commandd > 0x21 && commandd < 0x30) || (commandd > 0x33 && commandd < 0x40) || (commandd > 0x43 && commandd < 0x51) || commandd > 0x76)
    {
        sc_regSet(5, 1);
        return -1;
    }
    *operand = operandd;
    *command = commandd;
    return 0;
}

int main()
{
    // sc_memoryInit();
    // sc_memorySet(10, 11);
    //  int o = 0;
    //  sc_memoryGet(2, &o);
    // char a[9] = "text.txt";
    // sc_memorySave(*&a);
    // sc_memoryLoad(*&a);
    sc_regInit();
    int register1 = 2;
    int value = 0;
    sc_regSet(register1, value);
    // register1 = 4;
    // value = 1;
    // sc_regSet(register1, value);

    // register1 = 1;
    // value = 2;
    // sc_regSet(register1, value);
    printf("%d", flag);
    printf("\n");

    sc_regGet(register1, &value);
    printf("%d", value);
    printf("\n");

    // register1 = 4;

    // value = 2;
    // sc_regSet(register1, value);
    // printf("%d", flag);
    // register1 = 3;
    int command = 0x70;
    int operand = 125;
    sc_regGet(register1, &value);
    sc_commandEncode(command, operand, &value);
    sc_commandDecode(value, &command, &operand);
    printf("value = %d\n",value);
    printf("%d   %d", command, operand);
    printf("\n");
}