#pragma once
// Dispositivo Generico : todas las clases de dispositivos de entrada derivan de aqui

class cGenericDevice // clase abstracta (instanciación imposible)
{
public:
	virtual void Init() = 0;
	virtual void Deinit(void) = 0;
	virtual void Update(void) = 0;
	virtual float Check(unsigned luiEntry) = 0;
	virtual bool IsValid(void) = 0;
};