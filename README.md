# [](https://github.com/Caelence/DiscordMessageDeleter#discordmessagedeleter)DiscordMessageDeleter
A simple tool designed to quickly and easily delete entire Discord conversations. 

- No installation is required.

``Please note``: This application cannot delete everything quickly. Discord's API rate limits message deletions for user accounts. Don't expect to delete a ton of messages super fast. This app is mainly meant to run in the background, and that's unfortunately the best that any app trying to do this can offer you.
This is not the fault of the app, but a safety feature implimented on Discord's side.

## Disclaimer:
- Automating a Discord user account is technically against Discord's ToS.
- By using this application, you take full responsibility for what might happen to your account.

>Sorry, I have to say that for legal reasons, but please don't let that scare you. I have used this app for deleting converstions with 70,000+ messages, and Discord has never taken any action on my account. This is not advice, but just my experience.

## How to use:
Please head over to [the wiki](https://github.com/Caelence/DiscordMessageDeleter/wiki) for guidance on how to use the application.

## How to build:
Building this application for Windows is simple. 
- Make sure you're using [Visual Studio 2022](https://visualstudio.microsoft.com/vs/community/) or newer.
- Make sure you have [vcpkg](https://github.com/Microsoft/vcpkg) installed. If not, you will have to manually build and compile each of the libraries used in this project. 
- Install the libraries through ``vcpkg``. I have included ``Cpp-base64`` already in the project. So, only get  [Libcpr](https://github.com/libcpr/cpr#building-cpr---using-vcpkg), and [JsonCPP](https://github.com/open-source-parsers/jsoncpp#the-vcpkg-dependency-manager).
That should be all that's needed to build this project. It's pretty straightforward, especially if using ``vcpkg.``
>If you're not on Windows, you'll unfortunately have to figure this out for yourself. 

## Future plans:
Below are some things I consider adding to this app in the future. 
- ~~Command line usage. (Able to call the app ffrom the command line with options)~~ - ``Added``
- ~~An option to delete a certain amount of messages, or simply all of them.~~ - ``Added``
- ~~Support for more operating systems. Right now, this will probably be the easiest to do, as only a few things will need to be changed.~~ - ``Added - but might take some time before this gets any offical releases for other OSes. Might need help with this. Please submit a request to help in the issues section if you think you can help with this.`` 
- ~~A better set of menus. The most important would be showing the user a list of their conversations. The DM they wish to delete messages from could be selected there. Instead of manually retrieving the channel ID themselves.~~ - ``Added``
- Expand on the previously added feature by also giving the option for displaying servers.

## Going forward:
As I have now implimented (almost) everything into this application that I want, I won't be adding anything for now. That might/will change in the future, and any requests will be read. So, please submit suggestions if you have any. As of now, I just cannot think of ways to improve this.

## Suggestions:
Please feel free to leave me any suggestions in the ``issues`` section on this repository. I'll be happy to try and impliment ideas submitted by other users.

## Libraries used:
- [Libcpr](https://github.com/libcpr/cpr)
- [JsonCPP](https://github.com/open-source-parsers/jsoncpp)
- [Cpp-base64](https://github.com/ReneNyffenegger/cpp-base64)

## Inspiration:
Thank you to [4W](https://github.com/4W) for inspiring me to create this project.
I got a lot of my inspiration from their project, and if you're wanting to try understand how this program works in an easier language, I highly recommend checking out their project:
[DiscordDelete](https://github.com/4W/DiscordDelete).

I have since expanded their orginal program and included new features, which in my opinion, make the app run better.
