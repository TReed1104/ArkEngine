#ifndef ARKENGINE_USERINTERFACE_MANAGER_H_
#define ARKENGINE_USERINTERFACE_MANAGER_H_

#include <vector>
#include "UserInterface.h"

class UserInterfaceManager {
public:
	static UserInterfaceManager* GetInstance();

	UserInterfaceManager(UserInterfaceManager const&) = delete;
	void operator=(UserInterfaceManager const&) = delete;

	void RegisterInterface(UserInterface* newInterface);
	UserInterface* GetUserInterface(const std::string& userInterfaceName);
	bool SetInterfaceActiveState(const std::string& userInterfaceName, const bool& newState);
	void Close(void);

	void Update(const float& deltaTime);
	void Render(void);

private:
	std::vector<UserInterface*> interfaceRegister;
	
	UserInterfaceManager() {}
};

#endif