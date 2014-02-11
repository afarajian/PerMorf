

class Entry_class {
public:	
	QString WordForm;        //�� ����	
	QString PhonForm;        //�� ��
	QString SynCatCode;      //��� ��
	QString SynType;         //�����
	QString StressPattern;   //�� ʘ�
	QString Freq;            //���	
	int FreqNum;             //�����
};

//���� � ���
class HomoGraph_class {
public:
	bool Is_HomoG; //����������
	Entry_class Entry[5]; // ����� ���
};

// ����
class Affix_class {
public:
    QString	        Affix;       //��    
    QString         AffixType ;  //����    
    QString         AffixPhon ;  //�� �� ��    
    QString         AffixPhonSt ;//�� ʘ� ��
};

//�������
class Noun_class {
public:
	Entry_class Noun;              //ʘ� ��	
	Affix_class Plural;            //ʘ� ��    
	Affix_class INM_RCM_PEC_EZM;   //ʘ� ���������� ������    
	Affix_class COC;               //������
};

//�������
class Adj_class {
public:
	Entry_class Adj;      //ʘ� ��    
	Noun_class Noun;      //ʘ� ��	
	Affix_class CAM_SAM;  //ʘ� ��� �� ��    
};

//�����
class Num_class {
public:
	Entry_class Num; //��	
	Affix_class ONM; //ʘ� ���
	Noun_class Noun; //��	
};

//�����
class Adv_class {
public:
	Entry_class Adv;  //��	
	Noun_class Noun;  //��	
	Affix_class CAM_SAM; //ʘ� ��� �� ��    
};

//���� ���
class Prep_class {
public:
	Entry_class Prep;  //�����    
	Noun_class Noun;   //��
};

// �����
class Verb_class{
public:
	Affix_class PrefixNEG;       //�����	
	Affix_class PrefixIMP_CON;   //����� ����	
	QString Prefix;              //���	
	Entry_class Verb;            //��	
	Affix_class Inf;             //ʘ� ���	
	enum {Past,Present}Tense;    //��
	Affix_class PP;              //ʘ� �����
    Affix_class PEI;             //����� ��
    Affix_class PEC;             //� ����
};



//����
class Lexeme
{
public:
	QString Word;    //�� ����	
	QString Phoneme; //�� ��
	QString Cat;     //����	
	QString Stress;  //�� ʘ�
	QString Syll;    //����	
	bool Pitch;      //����	
	bool Bound;      //��
};

