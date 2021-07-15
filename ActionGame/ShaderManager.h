#pragma once

class ShaderManager : public Singleton<ShaderManager>
{
private:
	std::map<std::string, LPD3DXEFFECT> effects;

public:
	virtual ~ShaderManager();
	// Effect »ý¼º
	HRESULT CreateEffect(std::string name, LPCWSTR filename, DWORD flag);
	// Effect °¡Á®¿È
	LPD3DXEFFECT& GetEffect(std::string name);
};

