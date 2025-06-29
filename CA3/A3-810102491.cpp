#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef struct wallet 
{
    string Name;
    float Payment = 0;
}Wallet;

typedef struct transfer
{
	string Source; 
	string Destination;
	float Value;
}Transfer;


const char Seprator = ',';
const char  In_Line_Seprator = ';';
const char  Payer_Value__Seprator = ':';
const string Distribution_Type_1 = "equally";
const string Distribution_Type_2 = "unequally";
const string Distribution_Type_3 = "adjustment";


typedef vector<Wallet> Wallet_List;
typedef vector<string> List;
typedef pair<string,float> Factor;
typedef vector<Factor> Factor_List;
typedef vector<Transfer> Transfer_List;

void Read_Input(Wallet_List &List1 , List &List2 , string User_File_Path , string Payment_File_Path);
void Read_User_Name(Wallet_List &List, string File_Path);
void Read_Payment_List(List &List, string File_Path);
void Calculate_Debt(Wallet_List &Users_Wallet , List Purchase_List);
string Specify_Distribution_Type(string Str);
Factor_List Specify_Payers(string Str);
Factor_List Specify_Borrowers(string Str, string Distribution_Type);
void Equally_Distribution(Wallet_List &Users_Wallet , Factor_List &Payers , Factor_List &Borrowers);
void Unequally_Distribution(Wallet_List &Users_Wallet , Factor_List &Payers , Factor_List &Borrowers);
void Adjustment_Distribution(Wallet_List &Users_Wallet , Factor_List &Payers , Factor_List &Borrowers);
void Apply_Payment(Wallet_List &Users_Wallet , string Name ,float Payment_Amount);
void Apply_Debt(Wallet_List &Users_Wallet , string Name ,float Debt_Amount);
Transfer_List Process(Wallet_List &Users_Wallet);
Factor_List Specify_Creditors(Wallet_List Users_Wallet);
Factor_List Specify_Debtors(Wallet_List Users_Wallet);
void Sort(Factor_List &List);
bool Check_Transfer_End(Wallet_List Users_Wallet);
void Transfer_Operation(Transfer_List &List ,Wallet_List &Users_Wallet , Factor_List &Creditors_List , Factor_List &Debtors_List ,int &Creditor , int &Debtor);
float Round_Two_Place(float x);
float To_Two_Place(float x);
void Sort_Transfers(Transfer_List &List);
void Print_List(Transfer_List List);


int main(int argc ,char *argv[])
{
    Wallet_List Users_Wallet;
    List Purchase_List;
    Transfer_List Money_Transfer;

    Read_Input(Users_Wallet,Purchase_List , argv[1] , argv[2]);

    Calculate_Debt(Users_Wallet , Purchase_List);

    Money_Transfer = Process(Users_Wallet);

    Sort_Transfers(Money_Transfer);
    Print_List(Money_Transfer);

    return 0;
}

void Read_Input(Wallet_List &List1 , List &List2 , string User_File_Path , string Payment_File_Path)
{
	Read_User_Name(List1,User_File_Path);
    Read_Payment_List(List2,Payment_File_Path);
}

void Read_User_Name(Wallet_List &List , string File_Path)
{
    fstream fin;

    fin.open(File_Path,ios::in);

    int counter = 0;
    string temp_str;

    getline(fin,temp_str);
    while(getline(fin,temp_str))
    {
        counter ++ ;
        List.resize(counter);
        List[List.size() - 1].Name = temp_str;
    }

    fin.close();
}

void Read_Payment_List(List &List , string File_Path)
{
    fstream fin;
    fin.open(File_Path,ios::in);

    string temp_str;

    getline(fin,temp_str);
    while(getline(fin,temp_str))
    {
        List.push_back(temp_str);
    }
    fin.close();
}

void Calculate_Debt(Wallet_List &Users_Wallet , List Purchase_List)
{
    string Distribution_Type;
    Factor_List Payers;
    Factor_List Borrowers;

    for(int i=0 ; i < Purchase_List.size() ; i++)
    {
        Distribution_Type = Specify_Distribution_Type(Purchase_List[i]);
        Payers = Specify_Payers(Purchase_List[i]);
        Borrowers =  Specify_Borrowers(Purchase_List[i],Distribution_Type);

        if(Distribution_Type == Distribution_Type_1)
            Equally_Distribution(Users_Wallet,Payers,Borrowers);
        else if(Distribution_Type == Distribution_Type_2)
            Unequally_Distribution(Users_Wallet,Payers,Borrowers);
        else if(Distribution_Type == Distribution_Type_3)
            Adjustment_Distribution(Users_Wallet,Payers,Borrowers);
    }

}

string Specify_Distribution_Type(string Str)
{
    string State;
    stringstream str_stream(Str);
    getline(str_stream,State,Seprator);
    return State;
}

Factor_List Specify_Payers(string Str)
{
    Factor_List Payers;
    string Temp1;
    stringstream S1(Str);

    getline(S1,Temp1,Seprator);
    getline(S1,Temp1,Seprator);

    stringstream S2(Temp1);
    string Temp2;

    int counter = 0;
    while(getline(S2,Temp2,In_Line_Seprator))
    {
        counter ++;
        string Temp3;
        stringstream S3(Temp2);

        getline(S3,Temp3,Payer_Value__Seprator);
        Payers.resize(counter);
        Payers[counter - 1].first = Temp3;
        getline(S3,Temp3,Payer_Value__Seprator);
        Payers[counter - 1].second = stof(Temp3);
    }

    return Payers;
}

Factor_List Specify_Borrowers(string Str , string Distribution_Type)
{
    Factor_List Borrowers;
    string Temp1;
    stringstream S1(Str);

    getline(S1,Temp1,Seprator);
    getline(S1,Temp1,Seprator);
    getline(S1,Temp1,Seprator);

    stringstream S2(Temp1);
    string Temp2;

    int counter = 0;
    while(getline(S2,Temp2,In_Line_Seprator))
    {
        counter ++;
        if(Distribution_Type == Distribution_Type_1)
        {
            Borrowers.resize(counter);
            Borrowers[counter - 1].first = Temp2;
            Borrowers[counter - 1].second = 0;
        }
        else
        {
            string Temp3;
            stringstream S3(Temp2);
            getline(S3,Temp3,Payer_Value__Seprator);
            Borrowers.resize(counter);
            Borrowers[counter - 1].first = Temp3;
            getline(S3,Temp3,Payer_Value__Seprator);
            Borrowers[counter - 1].second = stof(Temp3);
        }      
    
    }

    return Borrowers;
}

void Equally_Distribution(Wallet_List &Users_Wallet , Factor_List &Payers , Factor_List &Borrowers)
{    
    float Total_Payment = 0;
    for(int i=0 ; i < Payers.size() ; i++)
    {
        Apply_Payment(Users_Wallet , Payers[i].first , Payers[i].second);
        Total_Payment += Payers[i].second;
    }

    if(Borrowers.size() == 0)
    {

        float User_Share = To_Two_Place(Total_Payment / Users_Wallet.size());

        for(int j=0 ; j < Users_Wallet.size() - 1 ; j++)
            Apply_Debt(Users_Wallet, Users_Wallet[j].Name , User_Share); 
        Apply_Debt(Users_Wallet , Users_Wallet[Users_Wallet.size() - 1].Name , Total_Payment - (User_Share * (Users_Wallet.size() - 1)));

    }
    else
    {
        float User_Share = To_Two_Place(Total_Payment / Borrowers.size());

        for(int j=0 ; j < Borrowers.size() - 1 ; j++)
            Apply_Debt(Users_Wallet , Borrowers[j].first , User_Share);
        Apply_Debt(Users_Wallet , Borrowers[Borrowers.size() - 1].first , Total_Payment - (User_Share * (Borrowers.size() - 1)));
    }
}

void Unequally_Distribution(Wallet_List &Users_Wallet , Factor_List &Payers , Factor_List &Borrowers)
{
    for(int i=0 ; i < Payers.size() ; i++)
    {
        Apply_Payment(Users_Wallet , Payers[i].first , Payers[i].second);
    }

    for(int j=0 ; j < Borrowers.size(); j++)
    {
        Apply_Debt(Users_Wallet , Borrowers[j].first , Borrowers[j].second);
    }
}

void Adjustment_Distribution(Wallet_List &Users_Wallet , Factor_List &Payers , Factor_List &Borrowers)
{
    float Total_Payment = 0;
    for(int i=0 ; i < Payers.size() ; i++)
    {
        Apply_Payment(Users_Wallet , Payers[i].first , Payers[i].second);
        Total_Payment += Payers[i].second;
    }

    float Additional_Payment = 0;
    for(int l=0 ; l < Borrowers.size() ; l++)
    {
        Additional_Payment += Borrowers[l].second;
    }

    float User_Share = To_Two_Place(Round_Two_Place(Total_Payment - Additional_Payment) / Users_Wallet.size());
    bool Apply_Flag;

    for(int j=0 ; j < Users_Wallet.size(); j++)
    {
        Apply_Flag = false;

        for(int k=0 ; k < Borrowers.size() ; k++)
        {
            if(Users_Wallet[j].Name == Borrowers[k].first)
            {
            	if(k == Borrowers.size() -  1)
            	{
            		Apply_Debt(Users_Wallet, Users_Wallet[j].Name , (Total_Payment - Additional_Payment) - (User_Share * (Users_Wallet.size() - 1)) + Borrowers[k].second);
            		Apply_Flag = true;
            		break;
            	}
                Apply_Debt(Users_Wallet, Users_Wallet[j].Name , User_Share + Borrowers[k].second);
                Apply_Flag = true;
                break;
            }
        }
        if(Apply_Flag != true)
            Apply_Debt(Users_Wallet, Users_Wallet[j].Name , User_Share);
    }
}

void Apply_Debt(Wallet_List &Users_Wallet , string Name ,float Debt_Amount)
{
    for(int i=0 ; i < Users_Wallet.size() ; i++)
    {
        if(Users_Wallet[i].Name == Name)
        {
            Users_Wallet[i].Payment -= Debt_Amount;
            break;
        }
    }
}

void Apply_Payment(Wallet_List &Users_Wallet , string Name ,float Payment_Amount)
{
    for(int i=0 ; i < Users_Wallet.size() ; i++)
    {
        if(Users_Wallet[i].Name == Name)
        {
            Users_Wallet[i].Payment += Payment_Amount;
            break;
        }
    }
}

Transfer_List Process(Wallet_List &Users_Wallet)
{
	Transfer_List List;

	Factor_List Creditors = Specify_Creditors(Users_Wallet);
	Factor_List Debtors = Specify_Debtors(Users_Wallet);

	Sort(Creditors);
	Sort(Debtors);

	int Current_Creditor = 0;
	int Current_Debtor = 0;

	while(Check_Transfer_End(Users_Wallet))
	{
		if(Current_Creditor > Creditors.size() - 1  || Current_Debtor > Debtors.size() - 1)
			break;
		Transfer_Operation(List ,Users_Wallet , Creditors , Debtors ,Current_Creditor , Current_Debtor);
	}
	return List;
}

Factor_List Specify_Creditors(Wallet_List Users_Wallet)
{
	Factor_List List;

	int counter = 0 ;
	for(int i=0 ; i < Users_Wallet.size() ; i++)
	{
		if(Users_Wallet[i].Payment > 0)
		{
			counter ++ ;
			List.resize(counter);
			List[counter - 1].first = Users_Wallet[i].Name;
			List[counter - 1].second = Users_Wallet[i].Payment; 
		}
	}
	return List;
}

Factor_List Specify_Debtors(Wallet_List Users_Wallet)
{
	Factor_List List;

	int counter = 0 ;
	for(int i=0 ; i < Users_Wallet.size() ; i++)
	{
		if(Users_Wallet[i].Payment < 0)
		{
			counter ++ ;
			List.resize(counter);
			List[counter - 1].first = Users_Wallet[i].Name;
			List[counter - 1].second = Users_Wallet[i].Payment; 
		}
	}
	return List;
}

void Sort(Factor_List &List)
{
	Factor Temp;

	for(int i=0 ; i < List.size() ; i++)
	{
		for(int j=0 ; j < List.size() - 1 ; j++)
		{
			if(abs(List[j].second) < abs(List[j + 1].second))
			{
				Temp = List[j] ;
				List[j] = List[j + 1];
				List[j + 1] = Temp;
			}
			else if(abs(List[j].second) == abs(List[j + 1].second))
			{
				if(List[j].first > List[j + 1].first)
				{
					Temp = List[j] ;
					List[j] = List[j + 1];
					List[j + 1] = Temp;
				}
			}
		}
	}
}

bool Check_Transfer_End(Wallet_List Users_Wallet)
{
	int counter = 0;

	for(int i=0 ; i < Users_Wallet.size() ; i++)
	{
		if(Users_Wallet[i].Payment == 0)
			counter ++;
	}

	if(counter == Users_Wallet.size())
		return false;
	else
		return true;
}

void Transfer_Operation(Transfer_List &List ,Wallet_List &Users_Wallet , Factor_List &Creditors_List , Factor_List &Debtors_List ,int &Creditor , int &Debtor)
{
	if(Creditors_List[Creditor].second > abs(Debtors_List[Debtor].second))
	{
		Apply_Payment(Users_Wallet , Debtors_List[Debtor].first , abs(Debtors_List[Debtor].second));
		Apply_Debt(Users_Wallet , Creditors_List[Creditor].first , abs(Debtors_List[Debtor].second));
		List.resize(List.size() + 1);
		List[List.size() - 1].Source = Debtors_List[Debtor].first;
		List[List.size() - 1].Destination = Creditors_List[Creditor].first;
		List[List.size() - 1].Value = abs(Debtors_List[Debtor].second);
		Creditors_List[Creditor].second = Round_Two_Place(Creditors_List[Creditor].second - abs(Debtors_List[Debtor].second));
		Debtors_List[Debtor].second = 0 ;	
		Debtor ++ ;	
	}
	else if(Creditors_List[Creditor].second < abs(Debtors_List[Debtor].second))
	{
		Apply_Payment(Users_Wallet , Debtors_List[Debtor].first , Creditors_List[Creditor].second);
		Apply_Debt(Users_Wallet , Creditors_List[Creditor].first , Creditors_List[Creditor].second);
		List.resize(List.size() + 1);
		List[List.size() - 1].Source = Debtors_List[Debtor].first;
		List[List.size() - 1].Destination = Creditors_List[Creditor].first;
		List[List.size() - 1].Value = Creditors_List[Creditor].second;
		Debtors_List[Debtor].second =  Round_Two_Place(Debtors_List[Debtor].second + Creditors_List[Creditor].second);
		Creditors_List[Creditor].second = 0;
		Creditor ++ ;
	}
	else
	{
		Apply_Payment(Users_Wallet , Debtors_List[Debtor].first , abs(Debtors_List[Debtor].second));
		Apply_Debt(Users_Wallet , Creditors_List[Creditor].first , Creditors_List[Creditor].second);
		List.resize(List.size() + 1);
		List[List.size() - 1].Source = Debtors_List[Debtor].first;
		List[List.size() - 1].Destination = Creditors_List[Creditor].first;
		List[List.size() - 1].Value = Creditors_List[Creditor].second;
		Debtors_List[Debtor].second = 0;
		Creditors_List[Creditor].second = 0;
		Creditor ++ ;
		Debtor ++ ;
	}
}

float Round_Two_Place(float x)
{
	return round(x * 100) / 100 ; 
}

float To_Two_Place(float x)
{
	return floor(x * 100) / 100;
}

void Sort_Transfers(Transfer_List &List)
{

	Transfer Temp;
	for(int i=0 ; i < List.size() ; i++)
	{
		for(int j=0 ; j < List.size() - 1 ; j++)
		{
			if(List[j].Value < List[j+ 1].Value)
			{
				Temp = List[j];
				List[j] = List[j + 1];
				List[j + 1] = Temp; 
			}
			else if(List[j].Value == List[j+ 1].Value)
			{
				if(List[j].Source > List[j+ 1].Source)
				{
					Temp = List[j];
					List[j] = List[j + 1];
					List[j + 1] = Temp;
				}
				else if(List[j].Source == List[j+ 1].Source)
				{
					if(List[j].Destination > List[j+ 1].Destination)
					{
						Temp = List[j];
						List[j] = List[j + 1];
						List[j + 1] = Temp;
					}
				}
			}	
		}
	}
}

void Print_List(Transfer_List List)
{
	for(int i=0 ; i< List.size() ; i++)
    {
    	cout << List[i].Source << " -> " << List[i].Destination << ": " << List[i].Value << endl;
    }
}