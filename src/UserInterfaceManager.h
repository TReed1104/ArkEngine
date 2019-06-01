#ifndef ARKENGINE_USERINTERFACE_MANAGER_H_
#define ARKENGINE_USERINTERFACE_MANAGER_H_

#include <vector>
#include "UserInterface.h"

class UserInterfaceManager {
public:
	static UserInterfaceManager* GetInstance();

	UserInterfaceManager(UserInterfaceManager const&) = delete;
	void operator=(UserInterfaceManager const&) = delete;

	void RegisterInterface(UserInterface& newInterface);
	void DeleteAllInterfaces(void);

	bool Update(const float& deltaTime);
	bool Render(void);

private:
	std::vector<UserInterface*> interfaceRegister;
	
	UserInterfaceManager() {}
};

#endif