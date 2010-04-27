#include "..\Input\InputManager.h"


void cInputManager::Init(const tActionMapping laActionMapping[], unsigned int luiActionCount){

	// Initializing the devices 
	cGenericDevice * lpKeyboard = new cKeyboard;
	lpKeyboard->Init(); // esto debe coincidír con los dispositivos enumerados
	
	// eKeyboard = 0 -> Keyboard in the index 0 of the vector
	mDevices.push_back(lpKeyboard); // asignando puntero lpKeyboard al vector de punteros Generic Devices

	// Inicializando el vector de las acciones
	mActions.resize( luiActionCount );

	// Initializing the mapping structure
	mMapped.resize( luiActionCount );
	int liIndex = 0;
	while ( laActionMapping[ liIndex ].miAction >= 0 )
	{
		cInputEntry lEntry;
		lEntry.muiDevice = laActionMapping[ liIndex ].miDevice;
		lEntry.muiChannel = laActionMapping[ liIndex ].miChannel;
		mMapped[ laActionMapping[ liIndex ].miAction].push_back(lEntry);

		++liIndex;
	}

}

void cInputManager::Update(const float &lfTimestep){

	// Update the devices
	int liSize = mDevices.size();
	for (int liDeviceId = 0; liDeviceId < liSize; ++liDeviceId){
		if (mDevices[liDeviceId] != NULL)
			mDevices[liDeviceId]->Update();
	}
	
	// for each action
	liSize = mMapped.size();
	for (int liActionId = 0; liActionId < liSize; ++liActionId){
		
		// For each map
		int liMapSize = mMapped[liActionId].size();
		float lfValue = 0.0f;

		for (int liMapId = 0; liMapId < liMapSize; ++liMapId)
		{
			// Calculate the value of the input
			const cInputEntry& lEntry = mMapped[liActionId][liMapId];
			lfValue += Check(lEntry.muiDevice, lEntry.muiChannel);
		}

		//Set the value in the action
		mActions[liActionId].Update(lfTimestep, lfValue);
	}
}

float cInputManager::Check(int liDevice, int liChannel){
	
	if (mDevices[liDevice] != NULL && mDevices[liDevice]->IsValid() )
		return (mDevices[liDevice]->Check(liChannel) );
	return 0.0f;
}

void cInputManager::Deinit(){

	// recuperar punteros a dispositivos dentro del vector mDevices
	int liSize = mDevices.size();  // Aqui hay una pequeña conversion signed / unsigned 
	//( se puede evitar en el siguiente bucle haciendo liDeviceId < mdevices.size pero VS-C++ lanza una advertencia)
	
	for (int liDeviceId = 0; liDeviceId < liSize; ++liDeviceId){ // recorriendo mDevices con el indice liDeviceId
		if (mDevices[liDeviceId] != NULL)
			mDevices[liDeviceId]->Deinit(); // Deinicializando dispositivos

			delete mDevices[liDeviceId]; // y liberando la memoria asignada de los punteros con delete 
		//( solo con los indices sin necesidad de iteradores, only Vectors can do it...  cool)
	}			
	mDevices.clear();	// limpiando el listado de punteros en el vector

	//liberar los benditos vectores comúnes con resize(0)
	mActions.resize(0);
	mMapped.resize(0);
	// Chau Input Manager !

}
