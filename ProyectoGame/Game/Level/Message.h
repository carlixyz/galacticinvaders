#pragma once

static const float kfMESSAGE_DELAY = 8.0f ;  // Inserte Aqui la duración del Mensaje

class cMessage
{
	bool mbMessageMode; //si es true se imprime el mensaje 
	const char * macMessage;
	//	char macMessage[64]; // Contenido del mensaje opcion original, modificada para mejorar el rendimiento
	float mfDelay;
	

public:

	void Init() { mbMessageMode = false;  mfDelay = 0.0f;   }// Inicializando variables varias kfDELAY = 5.0f;

	void SetMessage(std::string &lacMessage) {macMessage = lacMessage.c_str() ;  /*strcpy_s(macMessage ,  lacMessage.c_str()) ;*/ }// Asigna el Mensaje a escribirse const_cast<char *>(

	bool GetMessageMode() { return mbMessageMode;} // Devuelve true si se está imprimiendo el mensaje

	void SetMessageMode(bool lbMode) { mbMessageMode = lbMode; }// Asignar true si queremos que se imprima el Mensaje
	
	void Update( float lfTimestep){	// Actualiza el Mensaje con el Metodo de Yorman © 

		if (mbMessageMode){
			mfDelay += lfTimestep;
			if (mfDelay < kfMESSAGE_DELAY)
				return;
		mfDelay = 0.0f;
		mbMessageMode = false;
		}
	}
			
	void Render(){

		 if(this->mbMessageMode == true){
			cGraphicManager::Get().SetColor( eLightWhite, eBlack);// Renderiza el mensaje
			cGraphicManager::Get().WriteChars(40, 6, this->macMessage);

		}
	}
		
};