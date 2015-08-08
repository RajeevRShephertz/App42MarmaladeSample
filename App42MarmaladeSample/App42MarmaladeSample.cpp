#include "s3e.h"
#include "IwDebug.h"
#include "TestStorageService.h"
#include "TestUserService.h"

#define API_KEY    "67359321652c10b15fd5f659d096a2051745aa4f339b936d6ce5dccb165de863"
#define SECRET_KEY "2d44878dd428046f23bd4b3807ce83e982db9900f4c5a8305255da4764c76610"

// Main entry point for the application
int main()
{
    //Initialise graphics system(s)
    
    printf("\nHello\n");
    /**
     * Initialise App42API with your API_KEY and SECRET_KEY
     */
    App42API::Initialize(API_KEY, SECRET_KEY);
    App42API::setIsTraceEnabled(true);
    
    /*
     * User Service Test
     */
    TestUserService *testUserService = new TestUserService();
    testUserService->createUser();
    
    /*
     * Storage Service Test
     */
    TestStorageService *testStorageService = new TestStorageService();
    testStorageService->insertJsonDocument();
    
    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        //Update the input systems
        s3eKeyboardUpdate();
        s3ePointerUpdate();

        
        // Your rendering/app code goes here.


        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
    }

    //Terminate modules being used
    delete testStorageService;
    delete testUserService;
    // Return
    return 0;
}
