typedef struct CHS {
    unsigned short cyl; 
    unsigned short head; 
    unsigned short sec; 
} tCHS;

typedef struct ECHS {
    unsigned short cyl; 
    unsigned short head; 
    unsigned short sec; 
} tLARGE;

typedef struct IDECHS {
    unsigned short cyl; 
    unsigned short head; 
    unsigned short sec; 
} tIDECHS;

typedef struct LBA {
    unsigned int lba; 
} tLBA;

typedef struct PART {
    int activ;
    tCHS beg;
    tCHS end;
    tLBA lba_beg;
    int size;
} tPART;

int lba2chs(tLBA orig, tCHS *dest);
int lba2large(tLBA orig, tLARGE *dest);
int lba2idechs(tLBA orig, tIDECHS *dest);
int chs2large(tCHS orig, tLARGE *dest);
int chs2idechs(tCHS orig, tIDECHS *dest);
int chs2lba(tCHS orig, tLBA *dest);
int large2chs(tLARGE orig, tCHS *dest);
int large2idechs(tLARGE orig, tIDECHS *dest);
int large2lba(tLARGE orig, tLBA *dest);
int idechs2chs(tIDECHS orig, tCHS *dest);
int idechs2large(tIDECHS orig, tLARGE *dest);
int idechs2lba(tIDECHS orig, tLBA *dest);
int lba2chs(tCHS geometry, tLBA orig, tCHS *dest);

int hdd();