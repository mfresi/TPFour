//---------------------------------------------------------------------------

#pragma hdrstop

#include "four.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

four::four()
{
	IdCarte=Register_Card(PCI_9111DG,0);     // On enregistre la carte

	AO_9111_Config(IdCarte,P9111_AO_UNIPOLAR);  // On paramètre notre sortie

	AO_VWriteChannel(IdCarte,1,0);       // On envoie 0v sur la sortie

	AI_9111_Config(IdCarte,TRIG_INT_PACER,P9111_TRGMOD_SOFT,0); // on configure notre entrée

}

four::~four()
{
	Release_Card(IdCarte);//on libere la carte
}

int four::Lecture()
{
	  double tension;
		AI_VReadChannel(IdCarte,1, AD_B_10_V, &tension);  // lecture sur le port 1
		if (tension<=0) {
			return 0;
		} else {
		return  (51*tension)-73;
;       }

}

void four::Ecriture(float tension)
{
		AO_VWriteChannel(IdCarte,0,tension); //ecriture
}
