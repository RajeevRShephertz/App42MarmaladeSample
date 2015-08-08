//
//  TestUserService.h
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#ifndef __App42Cocos2dXSDK_3_0Beta2_Sample__TestUserService__
#define __App42Cocos2dXSDK_3_0Beta2_Sample__TestUserService__

#include <iostream>
#include "App42API.h"

class TestUserService : public App42CallBack
{
public:
   
    TestUserService();
    ~TestUserService();
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    void createUser();
    void createUserWithCustomData();
    void createUserWithRoles();
    void assignRoles();
    
    void authenticateUser();
    void authenticateUserViaEmail();
    void getUserWithUserName();
    void getUserWithCustomData();
    void getUserWithEmailId();
    void getUserInfo();
    void getAllUser();
    void getAllUsersByPaging();
    void getAllUsersCount();
    void lockUser();
    void unlockUser();
    void getLockedUsers();
    void getLockedUsersByPaging();
    void getLockedUsersCount();
    void updateEmail();
    void deleteUser();
    void changePassword();
    void resetPassword();
    void createOrUpdateProfile();
    void getUserByProfileData();
    void logout();
    void getRolesByUser();
    void deleteUserPermanent();

    void getUsersByRole();
    void revokeRole();
    void revokeAllRoles();
    void getUsersByGroup();
    void createUserWithProfile();
    void getAllUsersWithCustomData();
    
    void loadResponseScene();
    // a selector callback
    void onUserRequestCompleted(App42CallBack *sender, void *response);
    void menuCloseCallback();
private:
    std::string apiKey;
    std::string secretKey;
    UserService *userService;
};
#endif /* defined(__App42Cocos2dXSDK_3_0Beta2_Sample__TestUserService__) */
