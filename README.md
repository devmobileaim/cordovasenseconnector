#Secure your multiplatform application

With the increasing number of device's shapes, resolutions and features, developing a mobile application has become a real challenge for specialists. The application layout has to be responsive, the application has to meet design guidelines, new APIs and best practices proposed – even sometime imposed – by OS editors.

All these requirements increase the development costs and tend to reduce time spent on a less visible, but equally important feature: the application security. As a result, Gartner foresees that in 2015, 75% of mobile apps will fail basic security test.

AiM Services (http://www.aim-services.ch) and Sysmosoft (http://www.sysmosoft.com) developed in common a Cordova Plugin to help you secure your application
The Sysmosoft SDK first version was available for native iOS and Android applications but not for multi-platform environment.
Thus, thanks to AiM's experience, we decided to develop SenseConnector, a Cordova / Phonegap plugin exposing Sysmosoft SDK‘s features to HTML5 developers on mobile platforms.

Sysmosoft SENSE SDK allows two protection levels for the application.

**Offline protection**:

- Screenshots prevention
- Control of data copy/pasting from the application
- Rooted and jail-broken devices detection
- Hacking detection (reverse engineering) for iOS apps

**Online protection**:

- Strong authentication
- User login control based on contextual rules (geofencing)
- Application updates handling
- Creation of a secured channel between the application and the enterprise intranet for all http browser requests (assets, ajax request, REST http services, etc…)
- User inactivity detection
- Timeout session detection

Our plugin (SenseConnector) installation is based on the CLI (command line interface) provided by Cordova project. You can easily add the plugin to an existing Cordova project and automatically benefit from the offline protection. If you want to go further, you can setup the SENSE Server in just a few minutes.

SenseConnector Cordova plugin installation for iOS & Android

#Requirements
To perform the operation, the Cordova command-line interface CLI is used. It allows to have a custom project respecting Cordova development standards. The executables are developed using NodeJS and is installed using NPM, the package manager of NodeJS.

The NodeJS and NPM installation package can be found at the following address: http://nodejs.org/

It must be installed on MacOS with the latest version of XCode installed.

For Android, it is necessary to install the Android SDK with API 21 or later and Apache Ant to compile the project. Apache Ant must be in the path of the OS.


#Installation
To create a blank project that will serve as a base for html sources, the procedure is as follows :

- npm –g install cordova
- cordova create ProjectName ch.company.application.id ProjectName
- cd ProjectName
- cordova platform add ios
- cordova platform add android
- **Register on the Sysmosoft web site** : https://files.sysmosoft.com/sdk/sense-sdk.html
- cordova plugins add https://github.com/devmobileaim/cordovasenseconnector.git
- **Complete the sense-config.properties files** Add the value for `sec-server-url` and `sense-license` in the `sense-config.properties` for Android and iOS
- cordova build ios
- cordova build android
You have a project that you can edit or compile with XCode command line.

## iOS - Use the debugger
With the default SENSE SDK, the debugger is not usable. To enable the debug mode, you need to install the debug version of the SENSE SDK.

* Copy the `Debug` folder at path `YourAppRootFolder/plugins/ch.aimservices.cordova.plugins.sense/src/ios` to path `YourAppRootFolder/platforms/ios/YourApp/Plugins/ch.aimservices.cordova.plugins.sense`
* In Xcode, open the `Build Settings` of your application project and search for `FRAMEWORK_SEARCH_PATHS`
* Open the arrow to see two configurations, one for `Debug` and one for `Release`
* Edit the `Debug` part and add `/Debug` at the end of `"YourApp/Plugins/ch.aimservices.cordova.plugins.sense"`. ATTENTION, change the value of `YourApp`

Now, when you compile in Debug mode with Xcode, you are able to use the debugger.

## iOS - Support the SENSE logger
SENSE privides a logger to save logs on encrypted files then send logs to the server.

To enable this feature, you need to follow the next points.
The first point is to modify the `.pch` file of your application

* In Xcode, find the `YourApp-Prefix.pch.pch` file of your application. ATTENTION, change the value of `YourApp`
* At the end of the file, add `#import <sense/SFKPCHImport.h>`

The second point is to modify the CordovaLib.

* In Xcode, open the `CordovaLib.xcodeproj` containted in the your application workspace
* Open the `Build Phases -> Link Binary With Libraries`
* Drag and drop the `sense.framework` at path `YourAppRootFolder/platforms/ios/YourApp/Plugins/ch.aimservices.cordova.plugins.sense`
* Find the `CordovaLib_Prefix.pch` file
* At the end of the file, add `#import <sense/SFKPCHImport.h>`

#Validation
To test the Cordova project please follow the following procedure:

- sudo npm –g install ios-deploy
- sudo npm –g install ios-sim
- cordova run ios
- cordova run android

The application will run in the emulator and double tapping Cmd + Shift + H you can check the overview of the application is well hidden by the SENSE SDK. For Android it depends on the version of the os but clicking on the “Exposé” you should see a black thumbnail where the application should be.

#Packaging
To build the .ipa you can either use XCode or use the following command line :

- xcrun -sdk iphoneos PackageApplication -v $PWD/platforms/ios/build/device/ProjectName.app -o $PWD/platforms/ios/build/ ProjectName.ipa –embed ../ProjectName.mobileprovision

The development profile has been previously configured on the machine and the .mobileprovision file downloaded from the Apple site.
To build the APK you can use the standard building command of Cordova CLI.

