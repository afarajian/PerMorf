void Tokenizer1(QString InputFile,QString OutputFile,int *intWordCount,QString *m_Wait) ;
void Tokenizer2(QString InputFile,QString OutputFile,QString *m_Wait,int *Repeat) ;
void Syntactical_Parser(QString FileName) ;

bool ReadEntry(QFile *FileName,HomoGraph_class *HomoGraphGrid,int Counter,QSqlDatabase *pConn) ;

int CodeFind(QFile *FileName,Entry_class *W1,Entry_class *W2,int W1idx,int W2idx,
	     int Limit,Entry_class *Abb,HomoGraph_class *HomoGraphGrid,QSqlDatabase *pConn) ;

void Categorizer(Entry_class *Entry,QTextStream *outStream,int *Repeat,QSqlDatabase *pConn) ;

void Optimizer1(Entry_class  *Entry,QTextStream& outStream,int *Repeat,QSqlDatabase *pConn) ;

bool SynCat_Check(QTextStream& outStream,Entry_class *Entry,Entry_class *LexEnt,QString *TempWord,int *Repeat,bool *blnUnKnown,QSqlDatabase *pConn) ;
bool Noun_rule(Entry_class  *Entry,Noun_class *Noun,QString *TempWord,bool 		*blnFound_Plural,bool *blnFoundCOC,bool *blnFoundINF,QSqlDatabase * pConn);

bool Adj_Rule(Adj_class *Adj,QString *TempWord,bool *blnFound_CAM_SAM,QSqlDatabase *pConn);

bool FindWord(QString strWord,Entry_class  *LexEnt,QSqlDatabase *pConn) ;
void NumRead(QString strWord,Entry_class *Entry,QSqlDatabase  *pConn);
bool Find_Num(QString strNum,QSqlDatabase  *pConn,Entry_class *LexEnt);
int power(int i,int j);

void Print_Word(QTextStream& outStream,Entry_class *Entry) ;

QString LeftTrim_VirtualSpace(QString *S) ;

bool SecondWord(QTextStream& outStream,Entry_class  *Entry,Entry_class  *LexEnt,
		QString *TempWord,int  *Repeat,bool *blnUnKnown,QSqlDatabase *pConn) ;

void Print_Noun_Suffix(QTextStream& outStream,Noun_class *Noun) ;

bool Is_Vowel(QString c) ;

bool Is_INM_RCM_PEC_EZM(Noun_class *Noun,QString strWord,QString *TempWord,QSqlDatabase *pConn,QString Is_V) ;
bool Is_COC(Noun_class *Noun,QString strWord,QString *TempWord,QSqlDatabase *pConn,QString Is_V);

bool Is_PEI_PRESENT(Verb_class *V,QString strWord,QSqlDatabase *pConn,QString Is_V) ;

bool Is_PEI_PP(Verb_class *V,QString strWord,QSqlDatabase *pConn,QString Is_V) ;

bool Is_PEI_PAST(Verb_class *V,QString strWord,QSqlDatabase *pConn,QString Is_V) ;

bool Is_PEC(Verb_class *V,QString strWord,QSqlDatabase *pConn,QString Is_V) ;

void Print_Verb(QTextStream& outStream,Verb_class *V,bool *blnFoundPPM,bool *blnFoundINF) ;

void Verb_Prefix_Rule(Entry_class *Entry,Verb_class *V ,QString *TempWord,QSqlDatabase *pConn) ;

bool FindVerb(QString strWord,Entry_class  *LexEnt,QSqlDatabase * pConn);
 
bool FindPrefixNEG(Verb_class *V,QString strWord,QSqlDatabase * pConn) ;

bool FindPrefixIMP_CON(Verb_class *V,QString strWord,QSqlDatabase * pConn) ;

bool  FindAffix(HomoGraph_class *HomoGraphGrid,Entry_class  *LexEnt,QString strWord,QSqlDatabase *pConn,int *rec2,int Counter) ;

int Ambiguity_Remover(HomoGraph_class *HomoGraphGrid,QSqlDatabase * pConn) ;

void Noun_Amb_Remover(HomoGraph_class *HomoGraphGrid,int W1idx,int W2idx,int *totshift) ;

void Adj_Amb_Remover(HomoGraph_class *HomoGraphGrid,int W1idx,int W2idx,int *totshift) ;

void Shift(HomoGraph_class *HomoGraphGrid,int ShiftNumber) ;

int CodeFind(QTextStream& outStream,Entry_class *W1,Entry_class *W2,int W1idx,int W2idx,int Limit,Entry_class *Abb,HomoGraph_class *HomoGraphGrid,QSqlDatabase * pConn) ;

void Categorizer(Entry_class *Entry,QTextStream& outStream,int *Repeat, QSqlDatabase *pConn) ;



