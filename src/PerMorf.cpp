
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
//#include <qapplication.h>
//#include <qfile.h>
//#include <qvariant.h> 
//#include <qsqldatabase.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <qtextstream.h>
#include<iostream>
#include <fstream>
//#include "Define.h"
//#include "Types.h" 
//#include "Functions.h"
using namespace std;

//Adjective Ambiguity  Remover
/*
void Adj_Amb_Remover(HomoGraph_class *HomoGraphGrid,int W1idx,int W2idx,int *totshift)
{
	int i;

	if (HomoGraphGrid[W2idx].Is_HomoG)
	{
		for(i=1;i<5;i++)	
			if (HomoGraphGrid[W2idx].Entry[i].SynCatCode=="CAM")      
		{
			HomoGraphGrid[W2idx].Entry[0]=HomoGraphGrid[1].Entry[i];
			break;
		}
		if (HomoGraphGrid[W2idx+1].Entry[0].SynCatCode.left(1)!="N")
			HomoGraphGrid[W2idx+1].Entry[0].SynCatCode="N6";
	}
	if (HomoGraphGrid[W2idx].Entry[0].SynCatCode=="CAM"||
		   HomoGraphGrid[W2idx].Entry[0].SynCatCode=="SAM")
	{
		HomoGraphGrid[W1idx].Entry[0].WordForm+=HomoGraphGrid[W2idx].Entry[0].WordForm;
		HomoGraphGrid[W1idx].Entry[0].SynCatCode="-1";
		Shift(HomoGraphGrid,1);
		(*totshift)++;
	}	
}


void Shift(HomoGraph_class *HomoGraphGrid,int ShiftNumber)
{
	int i;
	for (i=1;i<5-ShiftNumber;i++)
		HomoGraphGrid[i]=HomoGraphGrid[i+ShiftNumber];
}

//Noun Ambiguity Remover

void Noun_Amb_Remover(HomoGraph_class *HomoGraphGrid,int W1idx,int W2idx,int *totshift)
{
	int i;
	if (HomoGraphGrid[W2idx].Is_HomoG)
	{
		for(i=1;i<5;i++)
			if (HomoGraphGrid[W2idx].Entry[i].SynCatCode=="PLM"||
						 HomoGraphGrid[W2idx].Entry[i].SynCatCode=="INM"||
						 HomoGraphGrid[W2idx].Entry[i].SynCatCode=="PEC"||
						 HomoGraphGrid[W2idx].Entry[i].SynCatCode=="COC")
		{
			HomoGraphGrid[W2idx].Entry[0]=HomoGraphGrid[1].Entry[i];
			break;
		}

	}

	if (HomoGraphGrid[W2idx].Entry[0].SynCatCode=="PLM"||
		   HomoGraphGrid[W2idx].Entry[0].SynCatCode=="INM"||
		   HomoGraphGrid[W2idx].Entry[0].SynCatCode=="PEC"||
		   HomoGraphGrid[W2idx].Entry[0].SynCatCode=="COC")
	{
		HomoGraphGrid[W1idx].Entry[0].WordForm+=HomoGraphGrid[W2idx].Entry[0].WordForm;
		HomoGraphGrid[W1idx].Entry[0].SynCatCode="-1";
		Shift(HomoGraphGrid,1);
		(*totshift)++;
	}
	if ((HomoGraphGrid[W1idx].Entry[0].SynCatCode=="N3"||
		    HomoGraphGrid[W1idx].Entry[0].SynCatCode=="N4") &&
		    HomoGraphGrid[W2idx].Is_HomoG==true)

		for(i=1;i<5;i++)
			if (HomoGraphGrid[W2idx].Entry[i].SynCatCode=="N3"||
						 HomoGraphGrid[W2idx].Entry[i].SynCatCode=="N4")
	{
		HomoGraphGrid[W2idx].Entry[0].SynCatCode=HomoGraphGrid[W2idx].Entry[i].SynCatCode;
		break;
	}

	if (HomoGraphGrid[W1idx].Is_HomoG &&
		   (HomoGraphGrid[W2idx].Entry[0].SynCatCode=="N3")||
		   (HomoGraphGrid[W2idx].Entry[0].SynCatCode=="N4"))
		for(i=1;i<5;i++)
	{	
		if (HomoGraphGrid[W1idx].Entry[i].SynCatCode=="Sp")
		{
			HomoGraphGrid[W1idx].Entry[0]=HomoGraphGrid[W1idx].Entry[i];
			break;
		}
		if (HomoGraphGrid[W1idx].Entry[i].SynCatCode=="N3"||
				  HomoGraphGrid[W1idx].Entry[i].SynCatCode=="N4")
		{
			HomoGraphGrid[W1idx].Entry[0]=HomoGraphGrid[W1idx].Entry[i];
			break;
		}
	}	
}
int Ambiguity_Remover(HomoGraph_class *HomoGraphGrid,QSqlDatabase * pConn)
{
	int i,Len;
	int intTotalShift=0;

	Entry_class LexEnt;
	QString TempWord;
	bool blnFound;

	
    
	if (HomoGraphGrid[1].Entry[0].WordForm==")"&&
		   HomoGraphGrid[0].Is_HomoG==true)
	{
		for (i=1;i<5;i++)
			if (HomoGraphGrid[0].Entry[i].SynCatCode=="Al")
		{
			HomoGraphGrid[0].Entry[0]=HomoGraphGrid[0].Entry[i];
			break;
		}
	}	
	// if the 1st word is a noun may be the next word is plsuf or pec or coc
	if(HomoGraphGrid[0].Entry[0].SynCatCode.left(1)=="N")
		Noun_Amb_Remover(HomoGraphGrid,0,1,&intTotalShift);
	else if (HomoGraphGrid[0].Entry[0].SynCatCode.left(1)=="A")
	{
		Noun_Amb_Remover(HomoGraphGrid,0,1,&intTotalShift);
		Adj_Amb_Remover(HomoGraphGrid,0,1,&intTotalShift);
	}
	if (HomoGraphGrid[0].Entry[0].WordForm==C_mi||
		   HomoGraphGrid[0].Entry[0].WordForm==C_nemi)
	{
		HomoGraphGrid[0].Entry[0].WordForm+=HomoGraphGrid[1].Entry[0].WordForm;
        
		HomoGraphGrid[0].Entry[0].SynCatCode="V";
		Shift(HomoGraphGrid,1);
		intTotalShift++;
	}	

	if (HomoGraphGrid[0].Entry[0].SynCatCode=="Pr")
	{
		for (i=0;i<5;i++)
			if(HomoGraphGrid[1].Entry[i].SynCatCode=="N9")
		{
			HomoGraphGrid[1].Entry[0]=HomoGraphGrid[1].Entry[i];               
			break;
		}
		if (  HomoGraphGrid[1].Is_HomoG==true)
			for(i=0;i<5;i++)		   
				if (HomoGraphGrid[1].Entry[i].SynCatCode.left(1)=="N")
		{
			HomoGraphGrid[1].Entry[0]=HomoGraphGrid[1].Entry[i];
			break;
		}
	}
	if (HomoGraphGrid[0].Entry[0].SynCatCode=="V1" && 
		   HomoGraphGrid[0].Is_HomoG==true)
		for(i=1;i<5;i++)
			if (HomoGraphGrid[0].Entry[i].SynCatCode.left(1)!="V")
	{
		HomoGraphGrid[0].Entry[0]=HomoGraphGrid[0].Entry[i];
		break;
	}
	if (HomoGraphGrid[0].Entry[0].SynCatCode=="-1")
	{
		if (HomoGraphGrid[1].Entry[0].SynCatCode.left(1)!="C")  //may be the unknown is not  a verb
		{
			Len=(HomoGraphGrid[0].Entry[0].WordForm).length();
			for (i = 1;i<=Len;i++)
			{
				TempWord = HomoGraphGrid[0].Entry[0].WordForm.mid( 0, i);
				blnFound = FindWord(TempWord,&LexEnt,pConn);
			}
			if (LexEnt.SynCatCode.left(1)=="N"||
						 LexEnt.SynCatCode.left(1)=="A")
			{
				Noun_Amb_Remover(HomoGraphGrid,0,1,&intTotalShift);
				Noun_Amb_Remover(HomoGraphGrid,0,1,&intTotalShift);

			}
		}
	}
	return intTotalShift;
}

int CodeFind(QTextStream& outStream,Entry_class *W1,Entry_class *W2,int W1idx,int W2idx,int Limit,Entry_class *Abb,HomoGraph_class *HomoGraphGrid,QSqlDatabase * pConn)
{
	int i;
	int intTotalShift=0;
	
	intTotalShift=Ambiguity_Remover(HomoGraphGrid,pConn);

	*W1=HomoGraphGrid[W1idx].Entry[0];
	*W2=HomoGraphGrid[W2idx].Entry[0];

	if (HomoGraphGrid[W1idx].Entry[0].SynCatCode=="Nu"&& 
		   HomoGraphGrid[W2idx].Entry[0].PhonForm=="va")
		HomoGraphGrid[W2idx].Entry[0].PhonForm="o";


	for (i=1;i<Limit;i++)
		HomoGraphGrid[i-1]=HomoGraphGrid[i];
	   
	if (Abb->WordForm!=""&&W1->SynCatCode=="Si")
		W1->WordForm="";
		
	if ((W2->SynCatCode == "Si" && W2->WordForm != C_Comma) && (W1->WordForm != 
		    C_Period || W1->WordForm !=C_Question || W1->WordForm != C_Exclamatory )) 
		;
	if (W1->SynCatCode=="Ab") 
	{
		Abb->WordForm+=W1->WordForm;
		Abb->PhonForm+=W1->PhonForm;
		Abb->StressPattern+=W1->StressPattern;
		Abb->SynCatCode="Ab";
		
		if (W2->SynCatCode=="Si")
			W2->WordForm="";         // to omit signs between characters of abbreviations
	} 
	else if (W1->WordForm!=""&&(W1->SynCatCode!="Si"|| W2->SynCatCode!="Ab"))
	{
		
		outStream<<(W1->WordForm+"\n");
		outStream<<(W1->PhonForm+"\n");
		outStream<<(W1->SynCatCode+"\n");
		outStream<<(W1->StressPattern+"\n");
		outStream<<(W1->Freq+"\n");
	}
	if (W2->SynCatCode!="Si"&& W2->SynCatCode!="Ab"&& Abb->WordForm!="")
	{
		
		outStream<<(Abb->WordForm+"\n");
		outStream<<(Abb->PhonForm+"\n");
		outStream<<("N1\n");
		outStream<<(Abb->StressPattern+"\n");
		outStream<<(Abb->Freq+"\n");	  
		Abb->WordForm="";
		Abb->PhonForm="";
		Abb->StressPattern="";
		Abb->Freq="";
	}
	return intTotalShift;
}


bool SecondWord(QTextStream& outStream,Entry_class  *Entry,Entry_class  *LexEnt,
		QString *TempWord,int  *Repeat,bool *blnUnKnown,QSqlDatabase * pConn)
{
	unsigned int i;
	QString TempString;
	bool blnFound;
	int rec2=0;
	           
	for (i = 1;i<=(*TempWord).length();i++)
	{
		TempString = (*TempWord).left(i);
		blnFound = FindWord(TempString,LexEnt,pConn);
	}
	if (LexEnt->WordForm == "")
		for (i = 1;i<=(*TempWord).length();i++)
	{
		TempString = (*TempWord).left(i);
		blnFound=FindAffix(
				(HomoGraph_class *)NULL,LexEnt,TempString,pConn,&rec2,0) ; 
	}
	if (*TempWord != "")
	{
		if (*Repeat > 1) return true;
		if ((LexEnt->WordForm == C_mi ||LexEnt->WordForm ==C_ne||LexEnt->WordForm 	==C_nem||LexEnt->WordForm ==C_be));
		else
			*TempWord =(*TempWord).mid((LexEnt->WordForm).length());
		if ((*TempWord) == "")  
		{
			Print_Word(outStream,LexEnt);
			outStream<<("$$$$$\n");
			*blnUnKnown=false;
			return false;
		}
		SynCat_Check(outStream,Entry,LexEnt,TempWord,Repeat,blnUnKnown,pConn);                
	}
	return true;
}


void Print_Verb(QTextStream& outStream,Verb_class *V,bool *blnFoundPPM,bool *blnFoundINF)
{
	if (V->PrefixNEG.Affix!= "")
	{
		outStream<<(V->PrefixNEG.Affix+"\n");
		outStream<<(V->PrefixNEG.AffixPhon+"\n");
		outStream<<(V->PrefixNEG.AffixType+"\n");
		outStream<<(V->PrefixNEG.AffixPhonSt+"\n");
		outStream<<("&&&\n");
	}    
	if (V->PrefixIMP_CON.Affix!= "")
	{
		outStream<<(V->PrefixIMP_CON.Affix+"\n");
		outStream<<(V->PrefixIMP_CON.AffixPhon+"\n");
		outStream<<(V->PrefixIMP_CON.AffixType+"\n");
		outStream<<(V->PrefixIMP_CON.AffixPhonSt+"\n");
		outStream<<("&&&\n");
	}    
	outStream<<(V->Verb.WordForm+"\n");
	outStream<<(V->Verb.PhonForm+"\n");
	outStream<<(V->Verb.SynCatCode+"\n");
	outStream<<(V->Verb.StressPattern+"\n");
	outStream<<("&&&\n");
     
	if (*blnFoundINF )
	{
		outStream<<(V->Inf.Affix+"\n");
		outStream<<(V->Inf.AffixPhon+"\n");
		outStream<<(V->Inf.AffixType+"\n");
		outStream<<(V->Inf.AffixPhonSt+"\n");
		outStream<<("&&&\n");       
		return;
	}
    
	if (*blnFoundPPM ) 
	{
		outStream<<(V->PP.Affix+"\n");
		outStream<<(V->PP.AffixPhon+"\n");
		outStream<<(V->PP.AffixType+"\n");
		outStream<<(V->PP.AffixPhonSt+"\n");
		outStream<<("&&&\n");
	}    
	if (V->PEI.Affix!= "") 
	{
		outStream<<(V->PEI.Affix+"\n");
		outStream<<(V->PEI.AffixPhon+"\n");
		outStream<<(V->PEI.AffixType+"\n");
		outStream<<(V->PEI.AffixPhonSt+"\n");
		outStream<<("&&&\n");
	}    
	if (V->PEC.Affix!= "") 
	{
		outStream<<(V->PEC.Affix+"\n");
		outStream<<(V->PEC.AffixPhon+"\n");
		outStream<<(V->PEC.AffixType+"\n");
		outStream<<(V->PEC.AffixPhonSt+"\n");
		outStream<<("&&&\n");
	}
	outStream<<("$$$$$\n");
}


bool FindVerb(QString strWord,Entry_class  *LexEnt,QSqlDatabase * pConn)

{
	QString          strSQL("");
	QString          Word("");
	int  rec;
		
	QSqlQuery  rs(pConn);
		
	Word=strWord.utf8();
	
	strSQL="";
	strSQL.append("SELECT PhonologicalForm,WrittenForm,SynCatCode,Freq,StressPattern From Entries Where WrittenForm= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND SynCatCode IN ('V1','V2','V3','V4','V5')");
	strSQL.append("ORDER BY Freq DESC");
	
	rs.prepare(strSQL) ;
	rs.exec();

	rec=rs.size() ; 
	
	if (rec == 0) 
	{
		
		return false;
	}
	   
	if(rec!=0)
	{
		rs.first();
		LexEnt->WordForm=rs.value(C_Entries_WrittenForm).toString() ;
		LexEnt->WordForm=QString::fromUtf8(LexEnt->WordForm,-1);
		LexEnt->PhonForm=rs.value(C_Entries_PhonologicalForm).toString() ;
		LexEnt->SynCatCode=rs.value(C_Entries_SynCatCode).toString() ;

		LexEnt->StressPattern =rs.value(C_Entries_StressPattern).toString() ;
		}

	return true ;
}

bool FindPrefixIMP_CON(Verb_class *V,QString strWord,QSqlDatabase * pConn)
{
	QString           strSQL("");
	QString           Word("");
	int  rec;
		
	QSqlQuery  rs(pConn) ; 
		
	strWord=LeftTrim_VirtualSpace(&strWord);

	Word=strWord.utf8();
	strSQL.append("Select Affix,PhonologicalForm,AffixName, StressPattern ,Meaning From Affixes   Where Affix= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND Meaning IN('11','12')");
        
	rs.prepare(strSQL) ;
	rs.exec();

	rec=rs.size() ; 
	if (rec == 0) 
		return false;
	else
	{
		rs.first();
		V->PrefixIMP_CON.Affix=rs.value(C_Affixes_Affix).toString() ;
		V->PrefixIMP_CON.Affix=QString::fromUtf8(V->PrefixIMP_CON.Affix,-1);

		V->PrefixIMP_CON.AffixPhon=rs.value(C_Affixes_PhonologicalForm).toString() ;

		V->PrefixIMP_CON.AffixPhonSt=rs.value(C_Affixes_StressPattern).toString() ;

		V->PrefixIMP_CON.AffixType=rs.value(C_Affixes_Meaning).toString() ;

	}
	if (V->PrefixIMP_CON.AffixType=="11")
	{
		V->PrefixIMP_CON.AffixType="V1IMP";
			
	}
	else
		V->PrefixIMP_CON.AffixType="V1CON";
	return true ;
}


bool FindPrefixNEG(Verb_class *V,QString strWord,QSqlDatabase * pConn)
{
	QString        strSQL("");
	QString        Word("");
	int  rec;
	
	QSqlQuery  rs(pConn) ; 
	if (strWord!="") strWord=LeftTrim_VirtualSpace(&strWord); 
	Word=strWord.utf8();
	
	strSQL.append("Select Affix,PhonologicalForm,AffixName, StressPattern ,Meaning From Affixes   Where Affix= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND Meaning='10'");
	
	
	rs.prepare(strSQL) ;
	rs.exec();
	      
      
	rec=rs.size() ; 


	if (rec == 0) 
		return false;
	else
		
	{
		rs.first();
		V->PrefixNEG.Affix=rs.value(C_Affixes_Affix).toString() ;
		V->PrefixNEG.Affix=QString::fromUtf8(V->PrefixNEG.Affix,-1);

		V->PrefixNEG.AffixPhon=rs.value(C_Affixes_PhonologicalForm).toString() ;

		V->PrefixNEG.AffixPhonSt=rs.value(C_Affixes_StressPattern).toString() ;

		V->PrefixNEG.AffixType="NEG";
		
		return true;
	}
}

void Verb_Prefix_Rule(Entry_class *Entry,Verb_class *V ,QString *TempWord,QSqlDatabase * pConn)
{
	unsigned int i,ii;
	QString TempString,TempWord2;
	bool  blnFound_Prefix_NEG=false;
	bool  blnFound_IMP_CON=false;
	bool blnFound=false;
	Entry_class LexEnt;
          
	for (i = 1;i<=2;i++)
	{
		TempString = (Entry->WordForm).mid(0,i);
		blnFound_Prefix_NEG = FindPrefixNEG(V,TempString,pConn);
	}
         
	if (V->PrefixNEG.Affix != "")
	{
		if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);
		*TempWord = (Entry->WordForm).mid((V->PrefixNEG.Affix).length());
		if (*TempWord!="") 
			*TempWord=LeftTrim_VirtualSpace(TempWord);
		if (V->PrefixNEG.AffixPhon=="nay"&&(*TempWord).left(1)==C_a)
			*TempWord=C_A+(*TempWord).mid(1);		
	}
	else
		*TempWord = Entry->WordForm;
	for (i = 1 ;i<= 2;i++)
	{
		TempString = (*TempWord).left(i);
		blnFound_IMP_CON = FindPrefixIMP_CON(V,TempString,pConn);
		if (V->PrefixNEG.Affix != "" && V->PrefixIMP_CON.Affix==C_be)
		{
			blnFound_IMP_CON=false;
			V->PrefixIMP_CON.Affix="";
			V->PrefixIMP_CON.AffixPhon="";
		}
		if(blnFound_IMP_CON) 
		{
			TempWord2=(*TempWord).mid((V->PrefixIMP_CON.Affix).length());
			if (TempWord2!="") 
				TempWord2=LeftTrim_VirtualSpace(&TempWord2);
			for (ii = 1;ii<=(TempWord2).length() ;ii++) 
			{
				TempString = (TempWord2).mid(0, ii);
				blnFound=FindVerb(TempString,&LexEnt,pConn);
			}
			if (LexEnt.PhonForm!="") break;
		}
		if (LexEnt.PhonForm=="") 
		{
			blnFound_IMP_CON=false;
			V->PrefixIMP_CON.Affix="";
		}
	}       
	if (V->PrefixNEG.Affix!="" && blnFound_IMP_CON)
		V->PrefixNEG.AffixPhon="ne";
	if (V->PrefixIMP_CON.Affix != "") 
	{
		if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);
		*TempWord = (*TempWord).mid((V->PrefixIMP_CON.Affix).length());
		if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);
		if ((*TempWord).left(1) == "") *TempWord = (*TempWord).mid(1);
	}              
}


bool Is_PEI_PAST(Verb_class *V,QString strWord,QSqlDatabase * pConn,QString Is_V)
{	
	QString        strSQL("");
	QString        Word("");
	int  rec;
	
	QSqlQuery  rs(pConn) ; 
	if (strWord!="") strWord=LeftTrim_VirtualSpace(&strWord); 
	
	Word=strWord.utf8();
	strSQL.append("Select Affix,PhonologicalForm,AffixName,StressPattern, Meaning  From Affixes   Where Affix= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND Meaning='21'");
	strSQL.append("AND Vowel_OK='");
	strSQL.append(Is_V);
	strSQL.append("'");
	
	rs.prepare(strSQL) ;
	rs.exec();
	      
      
	rec=rs.size() ; 


	if (rec == 0) 
		return false;
	else
		
	{
		rs.first();
		V->PEI.Affix=rs.value(C_Affixes_Affix).toString() ;
		V->PEI.Affix=QString::fromUtf8(V->PEI.Affix,-1);
		V->PEI.AffixPhon=rs.value(C_Affixes_PhonologicalForm).toString() ;
		V->PEI.AffixPhonSt=rs.value(C_Affixes_StressPattern).toString() ;
		V->PEI.AffixType="PEI";         
             
		return true;
	}
}

bool Is_PEC(Verb_class *V,QString strWord,QSqlDatabase * pConn,QString Is_V)
{
	QString strWordR1("") ;
	QString strMeaning("");
	
	QString        strSQL("");
	QString        Word("");
	int  rec;
		
	QSqlQuery rs(pConn) ;
	QSqlQuery rs2(pConn) ;
	
	

	if (strWord!="") strWord=LeftTrim_VirtualSpace(&strWord); 
	
	Word=strWord.utf8();
	strSQL.append("Select Affix,PhonologicalForm,AffixName,StressPattern, Meaning  From Affixes   Where Affix= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND Meaning IN ('03','08')");
	strSQL.append("AND Vowel_OK='");
	strSQL.append(Is_V);
	strSQL.append("'");
	
	rs.prepare(strSQL) ;
	rs.exec();
	      
      
	rec=rs.size() ; 

		
		 
	if (rec == 0) 
		return false;
	else
	{
		rs.first();
		V->PEC.Affix=rs.value(C_Affixes_Affix).toString() ;
		V->PEC.Affix=QString::fromUtf8(V->PEC.Affix,-1);
		
		V->PEC.AffixType=rs.value(C_Affixes_Meaning).toString() ;
		
		V->PEC.AffixPhon=rs.value(C_Affixes_PhonologicalForm).toString() ;

		V->PEC.AffixPhonSt=rs.value(C_Affixes_StressPattern).toString() ;

		strMeaning.append(V->PEC.AffixType);
		          
		if (!QString::compare(strMeaning,"03"))
			V->PEC.AffixType = "PEC";			  
		else
			V->PEC.AffixType ="SUC";
	        
		return true;
	}
}

bool Is_PEI_PRESENT(Verb_class *V,QString strWord,QSqlDatabase *pConn,QString Is_V)
{
	QString        strSQL("");
	QString        Word("");
	int  rec;
	
	QSqlQuery  rs(pConn) ; 
	
	if (strWord!="") strWord=LeftTrim_VirtualSpace(&strWord); 
	
	Word=strWord.utf8();
	strSQL.append("Select Affix,PhonologicalForm,AffixName,StressPattern, Meaning  From Affixes   Where Affix= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND Meaning='20'");
	strSQL.append("AND Vowel_OK='");
	strSQL.append(Is_V);
	strSQL.append("'");
	
	rs.prepare(strSQL) ;
	rs.exec();
	      
      
	rec=rs.size() ; 


	if (rec == 0) 
		return false;
	else
		
	{
		rs.first();
		V->PEI.Affix = rs.value(C_Affixes_Affix).toString() ;
		V->PEI.Affix=QString::fromUtf8(V->PEI.Affix,-1);
		V->PEI.AffixPhon = rs.value(C_Affixes_PhonologicalForm).toString() ;  

		V->PEI.AffixPhonSt = rs.value(C_Affixes_StressPattern).toString() ;

		V->PEI.AffixType="PEI";
		      
		return true;      
	}
}

QString LeftTrim_VirtualSpace(QString *S)
{
	
	
	//if (((*S).left(1)==""))
	//	*S=(*S).mid(1);
		
			
	return (*S);
}


bool Is_PEI_PP(Verb_class *V,QString strWord,QSqlDatabase *pConn,QString Is_V)
{
	QString        strSQL;
	QString        Word;
	int  rec;
	
	QSqlQuery  rs(pConn) ; 
	if (strWord!="") strWord=LeftTrim_VirtualSpace(&strWord); 
	
	Word=strWord.utf8();
	strSQL.append("Select Affix,PhonologicalForm,AffixName,StressPattern, Meaning  From Affixes   Where Affix= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND Meaning='22'");
	strSQL.append("AND Vowel_OK='");
	strSQL.append(Is_V);
	strSQL.append("'");
	
	rs.prepare(strSQL) ;
	rs.exec();
	     
      
	rec=rs.size() ; 

	if (rec == 0) 
		return false;
	else
		
	{
		rs.first();
		V->PEI.Affix = rs.value(C_Affixes_Affix).toString() ;
		V->PEI.Affix=QString::fromUtf8(V->PEI.Affix,-1);
		V->PEI.AffixPhon= rs.value(C_Affixes_PhonologicalForm).toString() ;
		V->PEI.AffixPhonSt= rs.value(C_Affixes_StressPattern).toString() ;
		V->PEI.AffixType="PEI";
		
		return true;
	}
}

void NumRead(QString strWord,Entry_class *Entry,QSqlDatabase  *pConn)
{
	int i,j,Len;
	bool blnFound;
	QString strTemp[6],strNum;
	Entry_class LexEnt;

	QString NumSuffixPhon[4]=  {"","hezAr","milyun","milyArd"};
	
	

	for (i=0;i<5;i++) 
		strTemp[i]="";


	Len=(strWord).length();
	
	

	for (i=1;i<=(Len/3);i++)
		strTemp[i]=strWord.mid(Len-i*3,3);
	strTemp[i]=strWord.mid(0,Len-(i-1)*3);


	if((Len%3)==0)
		j=i-1;
	else 
		j=i;
	  
	for (;j>0;j--)
	{
	
		if (Entry->PhonForm!=""){
			if (Is_Vowel(LexEnt.PhonForm.right(1)))
				LexEnt.PhonForm+="yo";
			else
				LexEnt.PhonForm+="o";

			LexEnt.StressPattern+="W";

		}
		strNum=strTemp[j];
		blnFound=Find_Num(strNum,pConn,&LexEnt);
		if (strNum!="000") LexEnt.PhonForm+=NumSuffixPhon[j-1];
		LexEnt.StressPattern+="WS";


	}
	Entry->PhonForm=LexEnt.PhonForm;
	Entry->StressPattern=LexEnt.StressPattern;
	Entry->SynCatCode="No";




}

bool Find_Num(QString strNum,QSqlDatabase  *pConn,Entry_class *LexEnt)
{
	
	int intNumber,i;
	

	QString TempPhon,TempStress; 

	QString           strSQL;
	QString           Word;
	QString strN;
	
	int  rec,intN;
		
	QSqlQuery rs(pConn) ;
		
	intNumber=atoi(strNum);
	

	for (i=2;i>=0;i--)
	{

		if (LexEnt->PhonForm!="")
		{
			if (Is_Vowel(LexEnt->PhonForm.right(1)))
				LexEnt->PhonForm=LexEnt->PhonForm+C_yo;
			else
				LexEnt->PhonForm=LexEnt->PhonForm+C_o;
			LexEnt->StressPattern+="W";
		}

		if (intNumber<=20){
			strN=QString::number(intNumber,10);
			i=i-2;
		}
		else
		{
			intN=(int)(intNumber/power(10,i))*power(10,i);
			strN=QString::number(intN,10);
			}
			
			
		        intNumber=intNumber-intNumber/power(10,i)*power(10,i);
			
			
			
			
		if (strN.left(1)!="0") 
		{	    
		

	
			strSQL="";
			strSQL.append("SELECT PhonologicalForm,WrittenForm,StressPattern From Entries Where WrittenForm= '");
			strSQL.append(strN);   
			strSQL.append("'");
			
			rs.prepare(strSQL);
			rs.exec();
	   

			rec=rs.size();


		if (rec> 0) 
			{
				         
				
		rs.first();
		TempPhon=rs.value(C_Entries_PhonologicalForm).toString() ; 
		TempStress= rs.value(C_Entries_StressPattern).toString() ;

			LexEnt->PhonForm+=TempPhon;
			LexEnt->StressPattern+=TempStress;
			}
       

			
		}

		else

		LexEnt->PhonForm=(LexEnt->PhonForm).left((LexEnt->PhonForm).length()-1);

		
	}
   

	return true;



}


int power(int i,int j)
{
	int result=1,k;

	for (k=1;k<=j;k++)
		result*=i;
	return result;
}


void Verb_Rule(Entry_class *Entry,QString *TempWord,Verb_class *V,bool *blnFoundPPM ,bool *blnFoundINF,QSqlDatabase * pConn)
{
	unsigned int i;
	QString TempString,CodeL2;
	QString strCodeL2("");
	bool blnFound;
	
	QString Is_V;
	
	*blnFoundINF=false;
	*blnFoundPPM=false;

	if (Is_Vowel(V->Verb.PhonForm.right(1)))
		Is_V="1";
	else
		Is_V="0";
	TempString = (*TempWord).mid(0, 1);    
	if (TempString == C_he)
	{
		*blnFoundPPM = true;
		*TempWord = (*TempWord).mid(1);	 
		if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);
	}
	else
		*blnFoundPPM = false;
	CodeL2=(Entry->SynCatCode).left(2);
	strCodeL2.append(CodeL2);
    
	if (!QString::compare(strCodeL2,"V2")||!QString::compare(strCodeL2,"V3"))
	{
		if ((*TempWord).left(1) == C_ne && (*TempWord).left(2) != C_nad) 
		{
			*blnFoundINF = true;
			V->Inf.Affix=C_ne;
			V->Inf.AffixPhon="an";
			V->Inf.AffixPhonSt="S";
			V->Inf.AffixType="INF";
			V->Verb.SynCatCode="N1";
			return;
		}                             
		if (*blnFoundPPM )
		{
			V->PP.Affix=C_he;
			V->PP.AffixPhon="e";
			V->PP.AffixType="PERF";
			V->PP.AffixPhonSt="S";
			for (i = 1;i<=(*TempWord).length();i++)
			{
				TempString = (*TempWord).left(i);
				Is_PEI_PP(V,TempString,pConn,Is_V);}
		}
		else
			if (*TempWord!="") 
				*TempWord=LeftTrim_VirtualSpace(TempWord);        
		for (i = 1;i<=(*TempWord).length();i++)
		{
			TempString = (*TempWord).left(i);
			blnFound=Is_PEI_PAST(V,TempString,pConn,Is_V);
		}
	}
	else 	
		if(!QString::compare(strCodeL2,"V1")||!QString::compare(strCodeL2,"V5")||!QString::compare(strCodeL2,"V4"))
			for (i = 1;i<=(*TempWord).length();i++)
	{
		TempString = (*TempWord).left(i);
		blnFound=Is_PEI_PRESENT(V,TempString,pConn,Is_V);
	}
	if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);    
	*TempWord = (*TempWord).mid((V->PEI.Affix).length());
	if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);
	if (*TempWord != "") 
	{
		for (i = 1;i<=(*TempWord).length();i++)
		{
			TempString = (*TempWord).left(i);
			Is_PEC(V,TempString,pConn,Is_V);}
			if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);     
			*TempWord = (*TempWord).mid((V->PEC.Affix).length());
			if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);
	}
	blnFound=true;       
}


void Print_Prep(QTextStream& outStream,Prep_class *P)
{
	if (P->Prep.WordForm!="")
	{
		Print_Word(outStream,&P->Prep);
		Print_Noun_Suffix(outStream,&P->Noun);
	}	
}

void Prep_Rule(Prep_class *Prep,QString *TempWord,QSqlDatabase *pConn)
{
	unsigned int i;
	QString TempString;
	bool blnFound;
	QString  Is_v;
	
	if (Is_Vowel(Prep->Prep.PhonForm.right(1)))
		Is_v="1";
	else
		Is_v="0";
		  
	for (i = 1;i<=(*TempWord).length();i++)
	{
		TempString =(*TempWord).left(i);
		blnFound = 
		Is_INM_RCM_PEC_EZM(&(Prep->Noun),TempString,TempWord,pConn,Is_v); 
	}      
}


void Print_Adj(QTextStream& outStream,Adj_class *Adj)
{
	if (Adj->Adj.WordForm!="")
	{
		Print_Word(outStream,&Adj->Adj);
		if (Adj->CAM_SAM.Affix!="")
		{
			outStream <<(Adj->CAM_SAM.Affix+"\n");
			outStream <<(Adj->CAM_SAM.AffixPhon+"\n");
			outStream <<(Adj->CAM_SAM.AffixType+"\n");
			outStream <<(Adj->CAM_SAM.AffixPhonSt+"\n");
			outStream <<("&&&\n");
		}
		Print_Noun_Suffix(outStream,&Adj->Noun);
	}
}

bool Is_CAM_SAM(Affix_class *Affix,QString strWord,QString *TempWord,QSqlDatabase *pConn)
{
	QString        strSQL;
	QString        Word("");
	int  rec;
	
	QSqlQuery  rs(pConn) ; 
	if (strWord!="") strWord=LeftTrim_VirtualSpace(&strWord); 
	if (strWord.length()>(*TempWord).length()) return 0;
	
	
	Word=strWord.utf8();
	strSQL.append("Select Affix,PhonologicalForm,AffixName,StressPattern, Meaning  From Affixes   Where Affix= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND Meaning='06'");
	
	
	rs.prepare(strSQL) ;
	rs.exec();
	      
      
	rec=rs.size() ; 


	if (rec == 0) 
		return false;
	else
		
	{
		rs.first();
		Affix->Affix = rs.value(C_Affixes_Affix).toString() ;
		Affix->Affix =QString::fromUtf8((Affix->Affix),-1);
		Affix->AffixPhon=rs.value(C_Affixes_PhonologicalForm).toString() ;

		Affix->AffixPhonSt=rs.value(C_Affixes_StressPattern).toString() ; 
  
		return true;
	}
}

bool Adj_Rule(Adj_class *Adj,QString *TempWord,bool *blnFound_CAM_SAM,QSqlDatabase *pConn)
{
	unsigned int i;
	QString TempString;
	
	for (i = 1;i<=(*TempWord).length();i++)
	{
		TempString = (*TempWord).left(i);
		*blnFound_CAM_SAM = Is_CAM_SAM(&Adj->CAM_SAM,TempString,TempWord,pConn);
	}
	
	 
	if (Adj->CAM_SAM.AffixPhon == C_tar) 
		Adj->CAM_SAM.AffixType = "250";
	else if (Adj->CAM_SAM.AffixPhon == C_tarin)
		Adj->CAM_SAM.AffixType="260";                                 
	if (Adj->CAM_SAM.Affix == "")
		return false;          
	return true ;
}

void Print_Noun(QTextStream& outStream,Noun_class *Noun)
{
	outStream <<(Noun->Noun.WordForm+"\n");
	outStream <<(Noun->Noun.PhonForm+"\n");
	outStream <<(Noun->Noun.SynCatCode+"\n");
	outStream <<(Noun->Noun.StressPattern+"\n");
	outStream <<("&&&\n");   
}

void Print_Noun_Suffix(QTextStream& outStream,Noun_class *Noun)
{
	if (Noun->Plural.Affix!="")
	{
		outStream <<( Noun->Plural.Affix+"\n");
		outStream <<( Noun->Plural.AffixPhon+"\n");
		outStream <<( Noun->Plural.AffixType+"\n");
		outStream <<( Noun->Plural.AffixPhonSt+"\n");
		outStream <<( "&&&\n");
		Noun->Plural.Affix = "";
	}
	if (Noun->INM_RCM_PEC_EZM.Affix!="")
	{
		outStream <<( Noun->INM_RCM_PEC_EZM.Affix+"\n");
		outStream <<( Noun->INM_RCM_PEC_EZM.AffixPhon+"\n");
		outStream <<( Noun->INM_RCM_PEC_EZM.AffixType+"\n");
		outStream <<( Noun->INM_RCM_PEC_EZM.AffixPhonSt+"\n");
		outStream <<( "&&&\n");
		Noun->INM_RCM_PEC_EZM.Affix="";
	}
      
	if (Noun->COC.Affix!="")
	{
		outStream <<( Noun->COC.Affix+"\n");
		outStream <<( Noun->COC.AffixPhon+"\n");
		outStream <<( Noun->COC.AffixType+"\n");
		outStream <<( Noun->COC.AffixPhonSt+"\n");
		outStream <<( "&&&\n");
		Noun->COC.Affix = "";
	}
	outStream <<("$$$$$\n");
}

void Print_Num(QTextStream& outStream ,Num_class *Num,bool *blnFound2NUM)
{
	if (Num->ONM.Affix!=""||*blnFound2NUM)
	{
		Print_Word(outStream,&Num->Num);
		if (Num->ONM.Affix!="")
		{
			outStream <<(Num->ONM.Affix+"\n");
			outStream <<(Num->ONM.AffixPhon+"\n");
			outStream <<(Num->ONM.AffixType+"\n");
			outStream <<(Num->ONM.AffixPhonSt+"\n");
			outStream <<("&&&\n");
		}
		Print_Noun_Suffix(outStream,&Num->Noun);
	}	
}


bool Is_COC(Noun_class *Noun,QString strWord,QString *TempWord,QSqlDatabase *pConn,QString Is_V)
{
	QString        strSQL;
	QString        Word("");
	int  rec;
	
	QSqlQuery  rs(pConn) ; 
	
	if (strWord.length()>(*TempWord).length()) return 0;
	
	Word=strWord.utf8();
	
	strSQL.append("Select Affix,PhonologicalForm,AffixName,StressPattern, Meaning  From Affixes   Where Affix= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND Meaning='05'");
	strSQL.append("AND Vowel_OK='");
	strSQL.append(Is_V);
	strSQL.append("'");
	
	rs.prepare(strSQL) ;
	rs.exec();
	      
      
	rec=rs.size() ; 


	if (rec == 0) 
		return false;
	else
		
	{
		rs.first();
		Noun->COC.Affix = rs.value(C_Affixes_Affix).toString() ;
		Noun->COC.Affix =QString::fromUtf8((Noun->COC.Affix),-1);
		Noun->COC.AffixPhon = rs.value(C_Affixes_PhonologicalForm).toString() ;
		Noun->COC.AffixPhonSt = rs.value(C_Affixes_StressPattern).toString() ;

		Noun->COC.AffixType="COC";
		        
		return true;
	}
}

bool Is_INM_RCM_PEC_EZM(Noun_class *Noun,QString strWord,QString *TempWord,QSqlDatabase *pConn,QString Is_V)
{
	QString strWordR1 ;
	QString strT1(""),strT2(""),strMeaning("");
	
	QString        strSQL("");
	QString        Word("");
	int  rec;
		
	QSqlQuery rs(pConn) ;
	QSqlQuery rs2(pConn) ;
	
	

		if (strWord!="") strWord=LeftTrim_VirtualSpace(&strWord);
	if (strWord.length()>(*TempWord).length()) return 0;
	Word=(strWord).utf8(); 
	
	
		
		strSQL.append("Select Affix,PhonologicalForm,AffixName,StressPattern, Meaning  From Affixes   Where Affix= '");
		strSQL.append(Word);   
		strSQL.append("'");
		strSQL.append("AND Meaning IN ('01','03','04')");
		strSQL.append("AND Vowel_OK='");
		strSQL.append(Is_V);
		strSQL.append("'");
	
		rs.prepare(strSQL) ;
		rs.exec();
	      
      
		rec=rs.size() ; 


		
			
		 
	if (rec == 0) 
		return false;
	else
	{
		rs.first();
		if (Is_V && rec>=1&&((*TempWord).length())>1&& 
				  rs.value(C_Affixes_Meaning).toString()=="04") 
			rec=0 ;
		
		Noun->INM_RCM_PEC_EZM.Affix = rs.value(C_Affixes_Affix).toString() ;
		Noun->INM_RCM_PEC_EZM.Affix =QString::fromUtf8((Noun->INM_RCM_PEC_EZM.Affix),-1);

		Noun->INM_RCM_PEC_EZM.AffixPhon = rs.value(C_Affixes_PhonologicalForm).toString() ;

		Noun->INM_RCM_PEC_EZM.AffixPhonSt = rs.value(C_Affixes_StressPattern).toString() ; 

		Noun->INM_RCM_PEC_EZM.AffixType = rs.value(C_Affixes_Meaning).toString() ; 

		strMeaning.append(Noun->INM_RCM_PEC_EZM.AffixType);
		
	}
	strT1.append(Noun->Noun.WordForm);
	strT1.append(Noun->Plural.Affix);
	
	strT1=strT1.right(1);
   
	if ((strT1== C_A || strT1== C_v) && Noun->INM_RCM_PEC_EZM.Affix == 	C_y && (*TempWord).length() == 1) 
		strMeaning.append("04");  
	if (!QString::compare(strMeaning,"01"))
		Noun->INM_RCM_PEC_EZM.AffixType= "INM";
	else if (!QString::compare(strMeaning,"03"))
		Noun->INM_RCM_PEC_EZM.AffixType = "PEC";
	else
	{
		Noun->INM_RCM_PEC_EZM.AffixType= "kasreh";
		Noun->INM_RCM_PEC_EZM.AffixPhon = C_ye;
	}         
	return true ;
}



bool Is_PLM(Noun_class *Noun,QString strWord,QSqlDatabase *pConn,QString Is_V)
{
	QString        strSQL;
	QString        Word;
	int  rec;
	
	QSqlQuery  rs(pConn) ; 
	if (strWord!="") strWord=LeftTrim_VirtualSpace(&strWord);
	
	Word=strWord.utf8(); 
	strSQL="";
	
	strSQL.append("Select Affix,PhonologicalForm,AffixName,StressPattern, Meaning,Vowel_OK  From Affixes   Where Affix= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND Meaning='00'");
	strSQL.append("AND Vowel_OK='");
	strSQL.append(Is_V);
	strSQL.append("'");
	
	rs.prepare(strSQL) ;
	rs.exec();
	      
      
	rec=rs.size() ; 


	if (rec == 0) 
		return false;
	else
		
	{
		rs.first();
		Noun->Plural.Affix = rs.value(C_Affixes_Affix).toString() ;
		Noun->Plural.Affix =QString::fromUtf8((Noun->Plural.Affix),-1);
		Noun->Plural.AffixPhon = rs.value(C_Affixes_PhonologicalForm).toString() ; 
		Noun->Plural.AffixPhonSt = rs.value(C_Affixes_StressPattern).toString() ; 
		Noun->Plural.AffixType="PLM";
		
		return true;
	}
}

bool Is_Vowel(QString c)
{
	if (c=="a"||c=="A"||c=="aa"||c=="e"||c=="o"||c=="i"||c=="u")
		return true;
	else 
		return false;
}

bool Noun_rule(Entry_class  *Entry,Noun_class *Noun,QString *TempWord,bool 		*blnFound_Plural,bool *blnFoundCOC,bool *blnFoundINF,QSqlDatabase * pConn)
{
	unsigned int i;
	QString  Is_v;
	QString strPhonR1,TempString("");
	
	
	if (Is_Vowel(Noun->Noun.PhonForm.right(1)))
		Is_v="1";
	else
		Is_v="0";

	if((*TempWord).left(2)==C_hA && (*TempWord).length()==3 && 
		    (*TempWord).right(1)!=C_ye)
		*TempWord=C_hA;

	if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);	
	
	         
	for (i = 1;i<=(*TempWord).length();i++)
	{
		TempString = (*TempWord).left(i);
		*blnFound_Plural = Is_PLM(Noun,TempString,pConn,Is_v);  
		
		        
	}
	
	  
	
	
	if (Noun->Plural.Affix!= "" && (Entry->PhonForm).right(1) == "i")
		Noun->Plural.AffixPhon = "y" + Noun->Plural.AffixPhon;
        
	if (Noun->Plural.Affix!= "" && (Entry->PhonForm).right(1) == "i"
		   && Noun->Plural.AffixPhon != "yAn")
	{
		Entry->PhonForm = (Entry->PhonForm).mid(0, 
		(Entry->PhonForm).length() - 2) + "o";
		Noun->Plural.AffixPhon = "v" + Noun->Plural.AffixPhon;;
	}
	
	

	if ((Noun->Plural.Affix).length()>0)
	 *TempWord =(*TempWord).mid((Noun->Plural.Affix).length() );
	if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);
	if ((*TempWord).length() == 0) goto p1;
          
	
             
	if (Is_Vowel((Noun->Noun.PhonForm+Noun->Plural.AffixPhon).right(1)))
		Is_v="1";
	else
		Is_v="0";
	
	

	for (i = 1;i<=(*TempWord).length();i++)
	{
	TempString = (*TempWord).left(i);
	
	*blnFoundINF = Is_INM_RCM_PEC_EZM(Noun,TempString,TempWord,pConn,Is_v);
		
		
	}
	
	
	if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);
	
	*TempWord =(*TempWord).mid((Noun->INM_RCM_PEC_EZM.Affix).length() );
	
	

	if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);
	if ((*TempWord) == "") goto p1;
             
	if
	(Is_Vowel((Noun->Noun.PhonForm+Noun->Plural.AffixPhon+Noun->INM_RCM_PEC_EZM.AffixPhon).right(1)))
		Is_v="1";
	else
		Is_v="0";
	
	
         
	for (i = 1;i<=(*TempWord).length();i++)
	{
		TempString = (*TempWord).left(i);
		*blnFoundCOC = Is_COC(Noun,TempString,TempWord,pConn,Is_v);
	}
	
	strPhonR1 = (Noun->Noun.PhonForm+Noun->Plural.AffixPhon+Noun->INM_RCM_PEC_EZM.AffixPhon).right(1);
	if (Noun->COC.AffixPhon == "ast" && Is_Vowel(strPhonR1) )
		Noun->COC.AffixPhon = "st";
                          
	if (*TempWord!="") 
		*TempWord=LeftTrim_VirtualSpace(TempWord); 
             
	*TempWord =(*TempWord).mid((Noun->COC.Affix).length());
	if (*TempWord!="")  *TempWord=LeftTrim_VirtualSpace(TempWord);

	if (*TempWord!="")  // maybe the affix is COC
	{
		Noun->INM_RCM_PEC_EZM.Affix="";
		*TempWord=Entry->WordForm.mid((Noun->Noun.WordForm).length());
		for (i = 1;i<=(*TempWord).length();i++)
		{
			TempString = (*TempWord).left(i);
			*blnFoundCOC = Is_COC(Noun,TempString,TempWord,pConn,Is_v);
		}
		strPhonR1 = (Entry->PhonForm+Noun->Plural.AffixPhon+Noun->COC.AffixPhon).right(1);
		if (Noun->COC.AffixPhon == "ast" && Is_Vowel(strPhonR1) )
			Noun->COC.AffixPhon = "st";
            
		if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord); 
             
		*TempWord =(*TempWord).mid((Noun->COC.Affix).length());
	}
	p1:
			if (Noun->Plural.Affix == "" && Noun->INM_RCM_PEC_EZM.Affix == "" &&
			Noun->COC.Affix == "" && *blnFoundINF == false) 
			return false;                
	return true;    	
}



bool IS_NUM(Num_class *Num,QString strWord,QSqlDatabase *pConn)
{
	QString        strSQL("");
	QString        Word("");
	int  rec;
		
	QSqlQuery rs(pConn) ;
	QSqlQuery rs2(pConn) ;
	
	

	if (strWord!="") strWord=LeftTrim_VirtualSpace(&strWord); 
	
	Word=strWord.utf8(); 
	strSQL="";
	
	strSQL.append("Select Affix,PhonologicalForm,AffixName,StressPattern, Meaning,Vowel_OK  From Affixes   Where Affix= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("AND Meaning='07'");
	
	
	
	rs.prepare(strSQL) ;
	rs.exec();
	      
      
	rec=rs.size() ; 
	 
	if (rec == 0) 
		return false;
	else
	{
		rs.first();
		Num->ONM.Affix = rs.value(C_Affixes_Affix).toString() ;
		Num->ONM.Affix =QString::fromUtf8((Num->ONM.Affix),-1);
		Num->ONM.AffixPhon = rs.value(C_Affixes_PhonologicalForm).toString() ; 
		Num->ONM.AffixPhonSt= rs.value(C_Affixes_StressPattern).toString() ;
		
		Num->ONM.AffixType="Card";
         
		return true;    
	}
}

void Num_Rule(QString *TempWord,Num_class *Num,bool *blnFoundNUM,QSqlDatabase *pConn)
{
	unsigned int i;
	QString TempString;
	 
	for (i = 1;i<=(*TempWord).length();i++) 
	{
		TempString =(*TempWord).left(i);
		*blnFoundNUM = IS_NUM(Num,TempString,pConn);
	}	
}


void Second_Num_Rule(QString *TempWord,Num_class *Num,bool *blnFoundNUM,QSqlDatabase *pConn)
{
	unsigned int i;
	QString TempString;
	bool blnFound=false;

	Entry_class LexEnt;

	for (i = 1;i<=(*TempWord).length();i++)
	{
		TempString =(*TempWord).left(i);
		blnFound = FindWord(TempString,&LexEnt,pConn);
		if (blnFound&&LexEnt.SynCatCode=="Nu") break;    
	}

	if (LexEnt.SynCatCode=="Nu"||LexEnt.SynCatCode=="A0")
	{
		*blnFoundNUM=true;
		Num->Num.WordForm+=LexEnt.WordForm;
		Num->Num.PhonForm+=LexEnt.PhonForm;
		Num->Num.StressPattern+=LexEnt.StressPattern;
		Num->Num.SynCatCode=LexEnt.SynCatCode;
		*TempWord=(*TempWord).mid((LexEnt.WordForm).length());
	}
}

bool SynCat_Check(QTextStream& outStream,Entry_class  *Entry,Entry_class  *LexEnt,
		  QString *TempWord,int  *Repeat,bool *blnUnKnown,QSqlDatabase *pConn)
{
	int ii,Len;
	QString strLeft1_SynCatCode ;
	QString TempString;
	bool blnSynCat_Check=false ;
	bool blnFoundNUM;
	bool blnFound2NUM;
	bool blnFound_Plural,blnFound_COC;
	bool blnFound_CAM_SAM;
	bool blnFoundPPM,blnFoundINF;
	bool blnFound;
		
	Num_class Num;
	Noun_class N;
	Adj_class Adj;
	Adv_class Adv;
	Verb_class V;
	Prep_class P;
	Affix_class Affix;
	 
	strLeft1_SynCatCode=(LexEnt->SynCatCode).left(1);
	if (LexEnt->SynCatCode == "V") goto vp;
	   
	if ((LexEnt->WordForm == C_mi ||LexEnt->WordForm ==C_ne||LexEnt->WordForm 	==C_nem||LexEnt->WordForm ==C_be)&&LexEnt->SynCatCode!="Nu")
	{
		*TempWord=Entry->WordForm;
		goto vp;
	}
	
	

	if (((*TempWord).left(2)==C_mi||(*TempWord).left(2)==C_nem||
		      (*TempWord).left(1)==C_be||((*TempWord).left(1)==C_ne&&(*TempWord).left(2)!=C_nad))&&LexEnt->SynCatCode!="Nu" &&(*TempWord).length()>2)
		goto vp;
		       
	if ((LexEnt->SynCatCode).left(2) == "Nu")
	{
		blnSynCat_Check = true;
		Num.Num=*LexEnt;

		Second_Num_Rule(TempWord,&Num,&blnFound2NUM,pConn);
		if (*TempWord!="")
			Num_Rule(TempWord,&Num,&blnFoundNUM,pConn);
		if (*TempWord!="") 
			*TempWord=LeftTrim_VirtualSpace(TempWord);
		*TempWord =(*TempWord).mid((Num.ONM.Affix).length());

		if (*TempWord!="") 
			*TempWord=LeftTrim_VirtualSpace(TempWord);
		blnSynCat_Check =Noun_rule(Entry,&Num.Noun,TempWord,&blnFound_Plural,&blnFound_COC,&blnFoundINF,pConn);
		if (*TempWord != "" && *Repeat > 1) return false;
		Print_Num(outStream,&Num,&blnFound2NUM);
	}
	else if ((LexEnt->WordForm != "") && (strLeft1_SynCatCode == "N"))
      
	{
		
		blnSynCat_Check = true;
		N.Noun=*LexEnt;
		blnSynCat_Check=Noun_rule(Entry,&N,TempWord,&blnFound_Plural,&blnFound_COC,&blnFoundINF,pConn);
		if (*TempWord != "" ) return false;        
		Print_Noun(outStream,&N);
		Print_Noun_Suffix(outStream,&N);
		
	}               
	else if (strLeft1_SynCatCode == "A" )
	
	{
		blnSynCat_Check = true;
		Adj.Adj=*LexEnt;
		Adj.Noun.Noun=*LexEnt;
		blnSynCat_Check=Adj_Rule(&Adj,TempWord,&blnFound_CAM_SAM,pConn);
		if (*TempWord!="") 		
			*TempWord=LeftTrim_VirtualSpace(TempWord);
		*TempWord =(*TempWord).mid((Adj.CAM_SAM.Affix).length()); 
		if (*TempWord!="") 
			*TempWord=LeftTrim_VirtualSpace(TempWord);
		blnSynCat_Check 
				=Noun_rule(Entry,&Adj.Noun,TempWord,&blnFound_Plural,&blnFound_COC,&blnFoundINF,pConn);

		if (Adj.Noun.Plural.Affix!="") 
			Adj.Adj.SynCatCode="N1";
		if (*TempWord != "" ) return false;
		
		Print_Adj(outStream,&Adj);
		
		
	}
	else if (strLeft1_SynCatCode == "P")
	
	{
		blnSynCat_Check = true;
		P.Prep=*LexEnt;
		Prep_Rule(&P,TempWord,pConn);
		if (*TempWord!="") 
			*TempWord=LeftTrim_VirtualSpace(TempWord);
		*TempWord 
				=(*TempWord).mid((P.Noun.INM_RCM_PEC_EZM.Affix).length());
		if (*TempWord!="") 
			*TempWord=LeftTrim_VirtualSpace(TempWord);
		if (*TempWord != "")  
			P.Noun.INM_RCM_PEC_EZM.Affix = "";
			
		if (*TempWord=="")
			Print_Prep(outStream,&P);
		if (*TempWord != "")
		{
			*blnUnKnown = true;
			return false;
		}
	}
	else if (strLeft1_SynCatCode == "V" )
	{		
            vp2:				
	        blnSynCat_Check = true;
		V.Verb=*LexEnt;
		Verb_Rule(LexEnt,TempWord,&V,&blnFoundPPM 	,&blnFoundINF,pConn);
		if(blnFoundINF)
		{
			if (*TempWord!="") 
				*TempWord=LeftTrim_VirtualSpace(TempWord);
			*TempWord = (*TempWord).mid(1);
			if (*TempWord!="") 
				*TempWord=LeftTrim_VirtualSpace(TempWord);
			Noun_rule(Entry,&N,TempWord,&blnFoundPPM,&blnFound_COC,&blnFoundINF,pConn);
		}
		if (*TempWord != "" ) return false;
						
		Print_Verb(outStream,&V,&blnFoundPPM,&blnFoundINF);
			if (blnFoundINF == true) 
			{
			Print_Noun_Suffix(outStream,&N);
			blnFoundINF = false;
			}
	}
	else if (strLeft1_SynCatCode == "C") 
		Print_Word(outStream,LexEnt);    
	else
	{
		vp:        	  				Verb_Prefix_Rule(Entry,&V,TempWord,pConn);       
		TempString = "";
		LexEnt->WordForm = "";
		Len=(*TempWord).length();
		for (ii = 1;ii<=Len ;ii++) 
		{
			TempString = (*TempWord).mid(0, ii);
			blnFound=FindVerb(TempString,LexEnt,pConn);
		}
		if (LexEnt->WordForm == "")
		{
		 if (V.PrefixIMP_CON.AffixPhon!="")
			{
			*TempWord=V.PrefixIMP_CON.Affix+(*TempWord);
			V.PrefixIMP_CON.Affix="";
			V.PrefixIMP_CON.AffixPhon="";
	               	Len=(*TempWord).length();
				for (ii = 1;ii<=Len ;ii++) 
				{
				TempString = (*TempWord).mid(0, ii);
				blnFound=FindVerb(TempString,LexEnt,pConn);
				}
			}
			if (V.PrefixNEG.Affix!="")
				{
				*TempWord=V.PrefixNEG.Affix+(*TempWord);
			      	V.PrefixNEG.Affix="";
				V.PrefixNEG.AffixPhon="";
				Len=(*TempWord).length();
				for (ii = 1;ii<=Len ;ii++) 
				{
					TempString =(*TempWord).mid(0, ii);
					blnFound=FindVerb(TempString,LexEnt,pConn);
   
				}
				}
				if (LexEnt->WordForm == "")
				{              
					*blnUnKnown = true;
					return false;
				}
				else
				{
					if (*TempWord!="") *TempWord=LeftTrim_VirtualSpace(TempWord);
			*TempWord = (*TempWord).mid((LexEnt->WordForm).length() );
					if (*TempWord!="") 
					*TempWord=LeftTrim_VirtualSpace(TempWord);
		     if (*TempWord == "" && LexEnt->WordForm == "")  return false;
				  
		     goto vp2;
					}				
				}
			else
				{
				if (*TempWord!="") 
					*TempWord=LeftTrim_VirtualSpace(TempWord);
		*TempWord =	(*TempWord).mid((LexEnt->WordForm).length() );
				if (*TempWord!="") 
					*TempWord=LeftTrim_VirtualSpace(TempWord);
				if (*TempWord == "" && LexEnt->WordForm == 	"")  return false;
					goto vp2;
				}
	}
	if ((*TempWord).left(2)==C_mi||(*TempWord).left(2)==C_nem||
		     (*TempWord).left(1)==C_be||((*TempWord).left(1)==C_ne&&(*TempWord).left(2)!=C_nad))
		goto vp;
	return blnSynCat_Check ;
}


void Print_Word(QTextStream& outStream,Entry_class *Entry)
{
	outStream<<(Entry->WordForm+"\n");
	outStream<<(Entry->PhonForm+"\n");
	outStream<<(Entry->SynCatCode+"\n");
	outStream<<(Entry->StressPattern+"\n");
	outStream<<( "&&&\n");
}


bool FindWord(QString strWord,Entry_class  *LexEnt,QSqlDatabase *pConn)
{
	QString        strSQL;
	QString        Word;
	int  rec;
	QSqlQuery  rs(pConn) ;
	QSqlQuery  rs2(pConn) ;
	Word=strWord.utf8();
	
	strSQL="";
	strSQL.append("SELECT PhonologicalForm,WrittenForm,SynCatCode,Freq,StressPattern From Entries Where WrittenForm= '");
	strSQL.append(Word);   
	strSQL.append("'");
	strSQL.append("Order By Freq Desc");

	rs.prepare(strSQL) ;
	rs.exec();


	rec = rs.size() ; 
	

	if (rec == 0)  
		return false;
	else
	{
	        rs.first();
	        LexEnt->WordForm = rs.value(C_Entries_WrittenForm).toString() ;
		LexEnt->WordForm =QString::fromUtf8((LexEnt->WordForm),-1);
                LexEnt->SynCatCode = rs.value(C_Entries_SynCatCode).toString() ; 
		LexEnt->PhonForm = rs.value(C_Entries_PhonologicalForm).toString() ;
		LexEnt->StressPattern = rs.value(C_Entries_StressPattern).toString() ; 
		LexEnt->Freq = rs.value(C_Entries_Freq).toString() ; 
		LexEnt->FreqNum=atoi(LexEnt->Freq);
		
		strSQL="";
		Word.append(LexEnt->SynCatCode);
		strSQL.append("SELECT Code,Type FROM SyntacticCategories WHERE Code='");
		strSQL.append(Word);   
		strSQL.append("'");
		
		QSqlQuery rs2(pConn) ;
		rs2.prepare(strSQL) ;
		rs2.exec();
		LexEnt->SynType= rs2.value(C_SyntacticCategories_Type).toString() ;
	}	
		
	return true;  
}

void Optimizer1(Entry_class  *Entry,QTextStream& outStream,int *Repeat,QSqlDatabase *pConn)
{
	Entry_class LexEnt; // Found entry in lexicon
	Affix_class Af;
	Noun_class N;
	Adj_class A;
	Verb_class V;

	QString TempWord;
	QChar TempC;
	bool blnFound;
	bool blnUnknown=false;
	
	int i,j=0;
	int Len;

	Entry_class Old_LexEnt;
	Entry_class LexEnt_Array[10];
	
	

	Len=(Entry->WordForm).length();
	
	
	for (i = 0;i<Len;i++)
	{
		
		TempWord +=(Entry->WordForm).at(i); 
		
		blnFound = FindWord(TempWord,&LexEnt,pConn);
		if (blnFound) {
			LexEnt_Array[j++]=LexEnt;
			
			
		
		}
				
				
				
				
	}
	j--;
	j--;
	
	
	
	

	if((Entry->WordForm).right(1) == C_te) 
	{
		TempWord =(Entry->WordForm).left((Entry->WordForm).length() - 1) + C_he;
		blnFound = FindWord(TempWord,&LexEnt,pConn);
		if (blnFound == true)
		{
			Entry->WordForm=LexEnt.WordForm;
			Entry->PhonForm=LexEnt.PhonForm +C_ye;
			Entry->SynCatCode=LexEnt.SynCatCode;
			Entry->StressPattern=(LexEnt.StressPattern).left((LexEnt.StressPattern).length()-1)+"WS";
		}
    
	}

	if ( LexEnt.WordForm.right(1)== C_he && ((Entry->WordForm).right(4) == C_hehAye|| (Entry->WordForm).right(5) == C_hehAi||	
		    (Entry->WordForm).right(5) == C_hehAyi))
	
		if  (LexEnt_Array[j].WordForm.right(1)==C_he)     
			LexEnt=LexEnt_Array[j];
	if (((Entry->WordForm).right(2) == 
		     C_At||(Entry->WordForm).right(3) ==C_gAn) &&
		     ((Entry->WordForm).right(3) 
		     !=C_hAt &&(Entry->WordForm).right(4) !=C_heAt))
	{
		if ((Entry->WordForm).right(2) == C_At) 
			TempWord = 
					(Entry->WordForm).left((Entry->WordForm).length() - 2) + C_he;
		else
			TempWord = (Entry->WordForm).left((Entry->WordForm).length() - 3) + C_he;

		blnFound = FindWord(TempWord,&LexEnt,pConn);
		if (blnFound == true)
		{
			Entry->PhonForm = 
					(Entry->PhonForm).left((Entry->PhonForm).length() - 
					1);
			Entry->StressPattern =
					(Entry->StressPattern).right((Entry->StressPattern).length() 	- 1);
			if ((Entry->WordForm).right(2) == C_At) 
				TempWord =C_At;
			else
				TempWord =C_gAn;

			goto sync;
		}
		else
			TempWord=Entry->WordForm;

	}

	
	
	
	if (LexEnt.SynCatCode=="No") 
	{
		Entry->PhonForm="";
		NumRead(TempWord,Entry,pConn);

		
		Entry->SynCatCode="Num";
		Entry->StressPattern="WS";
		Print_Word(outStream,Entry);
		outStream<<("$$$$$\n");
	}
	else
	{
		
		
		TempWord = TempWord.mid((LexEnt.WordForm).length() );
		
		if (TempWord!="") TempWord=LeftTrim_VirtualSpace(&TempWord);
       
		if (TempWord == "")
		{
			
			Print_Word(outStream,Entry);
			outStream<<("$$$$$\n");
		}          
		else      
			
			sync:      
			SynCat_Check(outStream,Entry,&LexEnt,&TempWord,Repeat,
				&blnUnknown,pConn);
		
		
		if (TempWord!="")
		{
			Old_LexEnt=LexEnt;
			for (i=j;j>=0;j--)
			{
				LexEnt=LexEnt_Array[i];
				TempWord=(Entry->WordForm).mid((LexEnt.WordForm).length());
				SynCat_Check(outStream,Entry,&LexEnt,&TempWord,Repeat,&blnUnknown,pConn);
				if (TempWord=="") break;
			}
		}			
		if (TempWord != "")
		{
			LexEnt=Old_LexEnt;
			TempWord=Entry->WordForm;
			Old_LexEnt=LexEnt;
			LexEnt.SynCatCode="V";
			SynCat_Check(outStream,Entry,&LexEnt,&TempWord,Repeat,&blnUnknown,pConn);
		}
		if  (TempWord != "")
		{
			LexEnt=Old_LexEnt;
			TempWord=Entry->WordForm;
			Old_LexEnt=LexEnt;
			SynCat_Check(outStream,Entry,&LexEnt,&TempWord,Repeat,&blnUnknown,pConn);
		}
		if (TempWord!="")
		{
			LexEnt=Old_LexEnt;
			outStream <<(LexEnt.WordForm+"\n");
			outStream <<(LexEnt.PhonForm+"\n");
			outStream <<(LexEnt.SynCatCode+"\n");
			outStream <<(LexEnt.StressPattern+"\n");
			outStream <<("&&&\n");	           
			TempWord=Entry->WordForm.mid((LexEnt.WordForm).length());
		}
		while (TempWord != "")
		{           
			if ((TempWord).length()>(LexEnt.WordForm).length())
				TempWord=TempWord.mid((LexEnt.WordForm).length());
			blnFound=SecondWord(outStream,Entry,&LexEnt,&TempWord,Repeat,&blnUnknown,pConn);   
			if (!blnFound) 
			{			   
				break;
			}
		}           
	}             
}


void Categorizer(Entry_class *Entry,QTextStream& outStream,int*Repeat,QSqlDatabase *pConn)
{
	bool blnUnKnown=false;
	Entry_class LexEnt; // Found entry in lexicon 
	bool blnFound=false;
	QString TempWord;

	if (Entry->SynCatCode == "") return;
	if (Entry->SynCatCode == "-1")
		Optimizer1(Entry,outStream,Repeat,pConn);
	else if (Entry->SynCatCode == "V")
	{
		TempWord=Entry->WordForm;
		SynCat_Check(outStream,Entry,Entry,&TempWord,Repeat,&blnUnKnown,pConn);
	}
	else
	{
			
		if (Entry->PhonForm.right(1)=="i"&& 
				  Entry->SynCatCode!="N4")
		{
				
			TempWord=(Entry->WordForm).left((Entry->WordForm).length()-1) ;
			blnFound = FindWord(TempWord,&LexEnt,pConn);
		  
			if (blnFound && LexEnt.FreqNum>Entry->FreqNum)
			{
				TempWord=(Entry->WordForm).mid((LexEnt.WordForm).length());
				SynCat_Check(outStream,Entry,&LexEnt,&TempWord,Repeat,&blnUnKnown,pConn);
			}
			else
			{
				outStream <<(Entry->WordForm+"\n");
				outStream <<(Entry->PhonForm+"\n");
				outStream <<(Entry->SynCatCode+"\n");
				outStream <<(Entry->StressPattern+"\n");
				outStream <<("&&&\n");
				outStream <<("$$$$$\n");
			}

		}

		else
		{
			outStream <<(Entry->WordForm+"\n");
			outStream <<(Entry->PhonForm+"\n");
			outStream <<(Entry->SynCatCode+"\n");
			outStream <<(Entry->StressPattern+"\n");
			outStream <<("&&&\n");
			outStream <<("$$$$$\n");	  
		}
		Entry->SynType="";
	}
}


void Syntactical_Parser(QString FileName)
{

	QFile inFile(FileName+"om1") ;
	
	if (! inFile.open(IO_ReadOnly) )
	{
		printf("%s","Could not open file for reading!!!");
		exit(0);
				    
	};
	
	QTextStream inStream(&inFile) ;
	
	QFile outFile(FileName+"op1") ;	
	
	if (! outFile.open(IO_WriteOnly) )
	{
		printf("%s","Could not open file for writing!!!");
		exit(0);
				    
	};
	
	
	       
	QTextStream outStream(&outFile) ;
	
	QString tempRead,tempWord,tempPhoneme,tempCat,tempStress;
	QString Word,Phoneme,Cat,Stress;
     
	while(!inStream.atEnd()) 
	{   
		inStream >>tempRead ; 
		
		
		if (tempRead=="&&&")
		{
			Word=Word+tempWord;
			Phoneme=Phoneme+tempPhoneme;
			Cat+=tempCat;
			Stress+=tempStress;
		}
		 
		else if (tempRead=="$$$$$")
		{
			if (Cat.left(3)=="NEG") 
			{
				Cat=Cat.mid(3,2);
				if (Phoneme.left(5)=="nay'A")
					Phoneme="nayA"+Phoneme.mid(5);
			}
			
				outStream << (Phoneme+" ");
			Word=""; 
			Phoneme="";
			Cat="";
			Stress="";
		}
		else 
		{
			tempWord=tempRead;
			
			inStream >> tempPhoneme ;
			
			inStream >> tempCat  ;
			
			
			inStream >>tempStress ;
			
		
		}
	}             
	inFile.close();
	outFile.close();
}
*/

//void Tokenizer2(QString InputFile,QString OutputFile,int *Repeat)
void Tokenizer2(string InputFile,string OutputFile){
/*
	int intTotalShift=0;
    
	QString  strTemp("") ;
	QString  strTemp2("");
	Entry_class W1,W2,Abb;

	HomoGraph_class HomoGraphGrid[5];
	int i;
	int Counter=0;
	bool blnFound=false;

	QSqlDatabase *pConn = QSqlDatabase::addDatabase( "QMYSQL3" ); // becomes the new default connection
	pConn->setHostName("localhost");
	pConn->setDatabaseName("lexicon");
	
	if (!pConn->open()){
		return;
		}

	QSqlQuery rs(pConn) ;
	QSqlQuery rs2(pConn) ;	
	
	QFile inFile(InputFile) ;
	
	if (! inFile.open(IO_ReadOnly) ){
		printf("%s","Could not open file for reading!!!");
		exit(0);
	};
     
	QFile outFile(OutputFile+"emif") ;
	
	if (!outFile.open(IO_WriteOnly) ){
		printf("%s","Could not open file for writing!!!");
		exit(0);
	};
	QTextStream outStream(&outFile) ;
    
	for (Counter=0;Counter<5;Counter++){
		blnFound=ReadEntry(&inFile, HomoGraphGrid, Counter, pConn);
           	if (!blnFound) break;
	}
	
	while(true){   
		intTotalShift=CodeFind(outStream,&W1,&W2,0,1,5,&Abb,HomoGraphGrid,pConn);           

		for (Counter=5-intTotalShift-1;Counter<5;Counter++){
			blnFound=ReadEntry(&inFile, HomoGraphGrid, Counter, pConn);
			if (!blnFound) break;
		}
        
		if (!blnFound) break;       
	}
	for (i=0;i<5-1;i++)	 
		CodeFind(outStream,&W1,&W2,i,i+1,1,&Abb,HomoGraphGrid,pConn);
	outStream<<(W1.WordForm+"\n");
	outStream<<(W1.PhonForm+"\n");		
	outStream<<(W1.SynCatCode+"\n");
	outStream<<(W1.StressPattern+"\n"); 
	outStream<<(W1.Freq+"\n"); 
	
	outStream<<(W2.WordForm+"\n");
	outStream<<(W2.PhonForm+"\n");
	outStream<<(W2.SynCatCode+"\n");
	outStream<<(W2.StressPattern+"\n");  
	outStream<<(W2.Freq+"\n");
	
	inFile.close();
	outFile.close();
	
	W1.WordForm="";

	QFile inFile2(OutputFile+"emif") ;
	if (! inFile2.open(IO_ReadOnly) ){
		printf("%s","Could not open file for reading!!!");
		exit(0);
	};
	QTextStream inStream(&inFile2) ;
     
	QFile outFile2(OutputFile+"om1") ;  
	if (!outFile2.open(IO_WriteOnly) ){
		printf("%s","Could not open file for writing!!!");
		exit(0);
	};
	
	QTextStream outStream2(&outFile2) ;
                      
	*Repeat=1 ;
	
	while(!inStream.atEnd()) {   
		inStream >> W1.WordForm ;
		inStream >> W1.PhonForm ;
		inStream >> W1.SynCatCode ;
		inStream >> W1.StressPattern ;
		inStream >> W1.Freq ;
		(W1.Freq).number(W1.FreqNum,10);
		Categorizer(&W1,outStream2,Repeat,pConn);       
	}
	inFile2.close();
	outFile2.close();
	pConn->close() ;
*/
}


///Amin: This Function is historically used for performing the basic tokenization.
///For now I disable it, and assume that the given file is already tokenized.
int Tokenizer1(string InputFile,string OutputFile)
{
/*
	const int intBufferBound = 500;
	int      intLoop,intCount;
	QString  strWord ;
	QString ArrayOfWords[intBufferBound];
	QString  strTemp("") ;
	QChar strBuf;
	if (InputFile=="") return ;
	QFile inFile(InputFile) ;
	
	QTextStream  inStream(&inFile);
     
	QFile outFile(OutputFile+"mif") ;
	
	QTextStream  outStream(&outFile);
	intCount=0;	 
    
	for (intLoop = 0;intLoop< intBufferBound;intLoop++)
		ArrayOfWords[intLoop] = "";
	
	while (!inStream.atEnd()) {  
		inStream>>strBuf; 
		strTemp=(QString)strBuf;
		if (strTemp!=C_Tanvin_Fathe && strTemp!=C_Tanvin_Zamme && strTemp!=C_Fathe && strTemp!=C_Zamme && strTemp!=C_Kasreh) strWord+=strTemp;
		if ((strTemp == C_Space) || (strTemp == C_Period) || (strTemp == C_Comma) || 
				   (strTemp == C_Question) || (strTemp == C_Exclamatory) || (strTemp == C_Semicolon) || 
				   (strTemp == C_Colon) || (strTemp == C_Open_Double_Quot) || (strTemp ==C_Close_Double_Quot) || 
				   (strTemp == C_Tilde) ||(strTemp == C_Slash) || (strTemp == C_Backslash)
				   || (strTemp == C_Open_Paren)||(strTemp == C_Close_Paren)){
			ArrayOfWords[intCount] = strWord.left((strWord).length() - 1);
			if (ArrayOfWords[intCount]!=""){
				outStream<<(ArrayOfWords[intCount]+"\n");
				(*intWordCount)++;
			}
			if (strTemp!=C_Space)
				outStream<<(strTemp+"\n");
			  
			strWord = "";
			intCount ++;
                           
			if (intCount == intBufferBound) intCount=1;
		}
	}
	ArrayOfWords[intCount] = strWord.left((strWord).length() );
	if (ArrayOfWords[intCount]!=""){
		outStream<<(ArrayOfWords[intCount]+"\n");
		(*intWordCount)++;
	}
	outStream<<(".\n");
	if (intCount == intBufferBound) intCount=1;
	inFile.close();
	outFile.close();
  */    
	return 1;

}


/*
bool  FindAffix(HomoGraph_class *HomoGraphGrid,Entry_class  *LexEnt,QString strWord,QSqlDatabase *pConn,int *rec2,int Counter)
{
	QString        strSQL;
	
	Entry_class  WTemp;

	int i;
	  

	QSqlQuery  rs(pConn) ;
	 
	strWord=strWord.utf8();
	strSQL="";
	strSQL.append("Select Affix,PhonologicalForm,AffixName,StressPattern  From Affixes   Where Affix= '");
	strSQL.append(strWord);   
	strSQL.append("'");
	
	rs.prepare(strSQL);
	rs.exec();
		
       

	*rec2=rs.size() ; 
	
	rs.first() ;

	if (*rec2 == 0) 
	{
		
		return false;
	}
	else
	{
		LexEnt->WordForm = rs.value(C_Affixes_Affix).toString() ;
		LexEnt->WordForm =QString::fromUtf8((LexEnt->WordForm),-1);
		LexEnt->PhonForm = rs.value(C_Affixes_PhonologicalForm).toString() ;  
		LexEnt->SynCatCode = rs.value(C_Affixes_AffixName).toString() ;  
		LexEnt->StressPattern= rs.value(C_Affixes_StressPattern).toString() ;
		
			               
	}
	if (*rec2>=1)
	{
		HomoGraphGrid[Counter].Is_HomoG=true;
		  
		for (i=0;i<*rec2;i++)
		{
			WTemp.WordForm = rs.value(C_Affixes_Affix).toString() ;
			WTemp.PhonForm = rs.value(C_Affixes_PhonologicalForm).toString() ;
			WTemp.SynCatCode = rs.value(C_Affixes_AffixName).toString() ;	
			WTemp.StressPattern = rs.value(C_Affixes_StressPattern).toString() ;
			HomoGraphGrid[Counter].Entry[*rec2+i]=WTemp;
			rs.next();
		}
	}
	
	
	return true;
}


bool ReadEntry(QFile *FileName,HomoGraph_class *HomoGraphGrid,int Counter,QSqlDatabase *pConn)
{
  
       
	
	QString   strWrittenForm ;
	QString   strPhonForm ;
	QString   strSynCatCode ;
	QString   strStressPat ;
	QString   strSQL ;
	QString    Word ;
	QString    strTemp("") ;
	QString    strTemp2("") ;
	
	
	int rec=0,rec2=0,i=0 ;
	Entry_class WTemp;
	QTextStream inStream(FileName);
	

	QSqlQuery rs(pConn) ;
	QSqlQuery rs2(pConn) ;

	HomoGraphGrid[Counter].Is_HomoG=false;
	for (i=0;i<5;i++)
	{
		HomoGraphGrid[Counter].Entry[i].WordForm="";
		HomoGraphGrid[Counter].Entry[i].PhonForm="";
		HomoGraphGrid[Counter].Entry[i].SynCatCode="";
		HomoGraphGrid[Counter].Entry[i].StressPattern="";
		HomoGraphGrid[Counter].Entry[i].SynType="";
		HomoGraphGrid[Counter].Entry[i].Freq="";
	}
	inStream>> (strTemp2);
	if(strTemp2=="")
		return 0;
	
	 strTemp=strTemp2.utf8();
              		
		Word.append(strTemp);
		strSQL="";
		strSQL.append("SELECT * FROM Entries WHERE WrittenForm='") ;
		strSQL.append(Word);   
		strSQL.append("'");
		strSQL.append("Order By Freq DESC");
       
		rs.prepare(strSQL) ;
		rs.exec() ;

		rec=rs.size();

		FindAffix(HomoGraphGrid,&WTemp,strTemp,pConn,&rec2,Counter) ; 
		if (rec == 0 &&rec2==0)
		{
			WTemp.WordForm = strTemp2;
		
			WTemp.SynCatCode = "-1";
			WTemp.PhonForm = "---";
			WTemp.StressPattern = "---";
			WTemp.Freq="0";
		}
		else if(rec!=0)
		{
			rs.first() ;
			
			WTemp.WordForm =strTemp2;
			
					         
			WTemp.PhonForm = rs.value(C_Entries_PhonologicalForm).toString() ;          
			WTemp.SynCatCode = rs.value(C_Entries_SynCatCode).toString() ;     
			WTemp.StressPattern = rs.value(C_Entries_StressPattern).toString() ;          
			WTemp.Freq = rs.value(C_Entries_Freq).toString() ; 
		}
		i=0;
		HomoGraphGrid[Counter].Entry[i]=WTemp;
		HomoGraphGrid[Counter].Is_HomoG=false;
       
		if (rec>1)
		{
			HomoGraphGrid[Counter].Is_HomoG=true;
			rs.next();
			for (i=1;i<rec;i++)
			{
				WTemp.WordForm = rs.value(C_Entries_WrittenForm).toString() ;
			
				WTemp.PhonForm = rs.value(C_Entries_PhonologicalForm).toString() ;
				WTemp.SynCatCode = rs.value(C_Entries_SynCatCode).toString() ;
				WTemp.StressPattern = rs.value(C_Entries_StressPattern).toString() ; 
				WTemp.Freq = rs.value(C_Entries_Freq).toString() ; 
				HomoGraphGrid[Counter].Entry[i]=WTemp ;
				rs.next() ;
				if (rs.at()<0) break;
			}
		}        
   
	  
	return true;
}

*/
void Gooya(string InputFile,string OutputFile)
{
//        int Repeat=0;
//        int intWordCount;
        Tokenizer1(InputFile,OutputFile);
       
        Tokenizer2(InputFile,OutputFile);
      /*  
        Syntactical_Parser(OutputFile);

        QFile outFile("C:\\F.txt") ;
        outFile.open(IO_WriteOnly) ;
    
        outFile.close();

        QFile::remove(OutputFile+"mif");
        QFile::remove(OutputFile+"emif");
*/
}

int main(int argc, char *argv[])
{
	string inputFile(argv[1]),outputFile(argv[2]);
	ifstream input( inputFile.c_str() );
	if( ! input.is_open() ){
		cout<<"Input file does not exist..."<<endl;
		return 0;
	}
/*
	QString inputFile(argv[1]),outputFile(outArg) ;
	QFile qf(inputFile) ;
	if (!qf.exists(inputFile))
	{
		printf("Input file not found!%s\n",inputFile.ascii()) ;
		return 0 ;
	}
	
	Gooya(inputFile,outputFile) ; 
	
	
	printf("Finished Successfully!\n");
	return EXIT_SUCCESS;
*/
	return 1;
}
