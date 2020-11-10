//*--------------------------------------------------------------------------------------------------------
//* BUT :  Ce programme a pour but de piloter un four
//* Nous pouvons le réguler en % ou en °C, et également afficher les valeurs sur une courbe
//*********************************************************************************************
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "IHMfour.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    ATTFOUR = new four(); //nouvel objet four
	Timer1->Enabled=true;  //on active le timer1 qui lit la temp et l'affiche
	 voltage=2;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
   temperature=ATTFOUR->Lecture(); //lecture de la température et stockage dans la variable 'temperature'
   LblTemp->Caption=temperature;  //affichage de la température
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	ATTFOUR->Ecriture(voltage); //ecriture

	if(temperature-2>tempcom) //si la temp actuelle est sup à la temp atendu
	{
		voltage=0;  //alors on met le voltage a 0 pour arreter de chauffer
	}
	if(temperature<tempcom) //si c'est inferieur
	{
		voltage+=0.2; //alors on chauffe progressivement
	}

	Chart1->Series[0]->Add(temperature); //affichage du graphique de la temp
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnStartClick(TObject *Sender)
{
	tempcom=EdtTemp->Text.ToInt();
	if (tempcom>65)  //on fixe l'edit à 65°C max
	{
	   tempcom=65;
       EdtTemp->Text=tempcom;
	}
	Timer2->Enabled= true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BtnArretClick(TObject *Sender)
{
ATTFOUR->Ecriture(0); //on met le voltage à 0V pour arreter de chauffer
voltage = 2 ;
Timer2->Enabled=false;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::ListTempChange(TObject *Sender)
{
	ATTFOUR->Ecriture(ListTemp->Text.ToDouble()/10); //ecriture du pourcentage en V
}
//---------------------------------------------------------------------------



