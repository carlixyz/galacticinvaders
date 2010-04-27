#pragma once
class cInputEntry
{
	public:
		unsigned muiDevice;
		unsigned muiChannel;
};

struct tActionMapping {
	int miAction;
	int miDevice;
	int miChannel;
};

// tActionMapping tiene una larga historia de recorridos primero empezó en InputConfiguration.h
// pero inputManager no lo reconocía como tipo en los parametros de su Init() 
// solamente lo aceptaba declarado al principio de su Header como se comenta en los apuntes pero considero
// que ya estaba bastante grande el fichero así que decidí incluirlo en este que está pequeñito

