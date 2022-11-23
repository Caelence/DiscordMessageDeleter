# [](https://github.com/Caelence/DiscordMessageDeleter#discordmessagedeleter)DiscordMessageDeleter
A simple tool designed to quickly and easily delete entire Discord conversations. 

- No installation is required.

``Please note``: This application cannot delete everything quickly. Discord's API rate limits message deletions for user accounts. Don't expect to delete a ton of messages super fast. This app is mainly meant to run in the background, and that's unfortunately the best that any app trying to do this can offer you.
This is not the fault of the app, but a safety feature implimented on Discord's side.

## Disclaimer:
- Automating a Discord user account is technically against Discord's ToS.
- By using this application, you take full responsibility for what might happen to your account.

>Sorry, I have to say that for legal reasons, but please don't let that scare you. I have used this app for deleting converstions with 70,000+ messages, and Discord has never taken any action on my account. This is not advice, but just my experience.

## How to install:
- Download the latest release from [here](https://github.com/Caelence/DiscordMessageDeleter/releases/latest).
- Extract all the files from the ``.zip`` to any location.
- Run ``DiscordMessageDeleter.exe``.

## Getting your token:
The hardest part of getting this program to work is getting your token.
Below are two methods that you can use to get your token:

### Easy - From web browser
#### - Recommended for most people
This method requires you to be signed into Discord in your web browser.
1. Go to [Discord.com](https://discord.com/login) and login.
2. Once in, press ``F12`` on your keyboard. This should open a window at either the bottom or the right of your browser. This differs from browser to browser, but the steps are roughly the same. If nothing pops up, please search up "How to open developer tools for ``browser name``."
3. In developer tools, find and click the ``Network`` tab at the top of the menu.![networkTab](https://user-images.githubusercontent.com/76179807/201469388-9d0aa46c-701d-4289-af51-b56a67c3bba3.png)
 Please note that your layout of buttons may be slighty different, but it will becalled ``Network``
4. Now in ``Network``, find the ``Filter URLs`` textbox. If you are unsure where to find the textbox, pressing ``Ctrl + F`` should select it for you. 
5. Inside the textbox, paste in the following: ``messages?limit=50``. (Without the period at the end)
6. Once you have pasted the text, click on a DM that you haven't opened yet.
7. After clicking on a DM, you should now see something similar to the following:![messagesLimit](https://user-images.githubusercontent.com/76179807/201469428-5a5fa02b-6775-466d-8e55-57ccd22b8262.png)
   If you do, click on ``GET``. A new window should popup.
    ``Note:`` If you don't see anything to click on, please try clicking a different DM. If you still don't get anything, try refreshing the page, and starting from the beginning.
8. You should now have a small window with more tabs in it. Make sure you are in the ``Headers`` tab.![headers](https://user-images.githubusercontent.com/76179807/201469446-519712fa-2fc0-4f04-a7f0-9fdc1b81f432.png)
9. In the ``Headers`` tab, scroll down until you find the ``Request Headers`` section.![requestHeaders](https://user-images.githubusercontent.com/76179807/201469452-380f9f91-52e1-40a2-bc5c-5bcb3d01dd2e.png)
10. In ``Request Headers``, find ``Authorization``. Select it, right click, and copy it. 
    ``Note``: For the safety of myself, I have hidden my ``Authorization`` in the image. You will see random characters here. 

You have now got your Discord Token! Copy this somewhere safe for usage in the application.
> Please do not share this with anyone! By sharing it, you may risk letting someone login to your account. With that being said, please do not worry about using this token in this application. It will not be sent to anyone. It is only kept on your computer, and no one else has access to it.

``Note``: You will have to do all of the previous steps each time you login/logout of Discord, as this token changes.

### Hard - From Discord app
#### - Only recommended if you don't want to sign into the browser
This method requires you to modify your ``settings.json`` in the ``discord`` folder in ``%appdata%``.

1. First, press ``Windows + R`` on your keyboard. This should open the following:

![run](https://user-images.githubusercontent.com/76179807/201470790-625f1140-57d1-4809-9787-af4345827b9f.png)

2. In the textbox, type in ``%appdata%/Discord/settings.json``
   ``Note``: If it asks you what you want to open it in, make sure you choose a text editor like Notepad, Notepad++, etc.. Just something that can open text files.
3. You should now see something similar to the following:

![settingsJson](https://user-images.githubusercontent.com/76179807/201470811-2926f504-1a94-4193-a8cf-373d88e463d1.png)

 ``Note``: Don't worry about the coloured text. Yours may just look plain.
 You may also not have all the lines that are shown in the previous image, but don't worry, that's just because of what your settings might be in Discord. Hence, ``settings.json``
4. In this file, you need to add:``"DANGEROUS_ENABLE_DEVTOOLS_ONLY_ENABLE_IF_YOU_KNOW_WHAT_YOURE_DOING": true,``
   after one of the previous lines. Preferably in the middle of the file. Example:

![settingJsonEdited](https://user-images.githubusercontent.com/76179807/201470828-7ec250f1-0884-4cf3-85d1-856bd66c7080.png)

5. After you have inserted the previous line into the file, save it, and quit.
6. Restart your Discord. Make sure it's closed, and doesn't appear in the system tray.
7. Once you have restarted your Discord, you should now be able to open the Developer tools in it. You can test that it's working by pressing ``Ctrl + Shift + i``. If something pops up, congratulations! If not, you edited the ``settings.json`` incorrectly, and will need to make sure it contains the line: ``"DANGEROUS_ENABLE_DEVTOOLS_ONLY_ENABLE_IF_YOU_KNOW_WHAT_YOURE_DOING": true,`` in the middle of it. (Including the ``,`` at the end.) If you still cannot get it to show, please try the following [guide](https://futuregaming.io/discord/how-to-enable-discord-developer-tools/).
8. Now that you have enabled Developer Tools in Discord, please follow the [Easy Guide](https://github.com/Caelence/DiscordMessageDeleter/blob/master/README.md#easy---from-web-browser) from step 3. (You can skip steps 1, and 2.)
9. When you get to step 7, click on ``messages?limit=50`` under ``Name`` instead of clicking ``GET``.
10. You should now have your token. Congratulations, you got it the hard way! I don't know why you'd want to do it this way, but you did it! You can now close the ``Developer Tools`` by pressing ``Ctrl + Shift + i`` again. 

``Note``: After doing this method, you will always be able to open Developer Tools in Discord. To disable that, please remove: ``"DANGEROUS_ENABLE_DEVTOOLS_ONLY_ENABLE_IF_YOU_KNOW_WHAT_YOURE_DOING": true,`` from ``settings.json``.

## Getting the channel ID:
Getting the channel ID is far easier than getting the Token. 
Please continue to follow the method that you chose earlier.

### The best option - Use the built-in channel lister
As of version 1.8.0 of this app, you now no longer need to manually get the channel ID each time you want to delete from a specific channel. You now only need the token to be able to delete messages. To use this feature, when asked ``Do you want to manually enter the channel ID? (y/N)`` just hit ``Enter`` or type ``n`` into the console. This option will automatically bring up more options asking you what you wish to display. 
``Note``: Support for displaying servers that you're in is not part of the app, *yet*. This is a planned feature, but for now, please manually enter the channel ID of the server channel you wish to delete from.

### Easy - From web browser
1. To get the channel ID from the browser, simply click on the DM that you wish to delete messages from. You should now notice that the URL will look similar to the following:
![url](https://user-images.githubusercontent.com/76179807/201471484-57ce607c-cbb3-4d36-b4e4-31a9c13c3540.png)

2. All you have to do is copy the last sections of numbers after the last ``/``. 
For example: ``101010101010101010``.
You have now got the channel ID.

3. Paste that into the application when asked for it.

### Hard - From Discord app
1. If not open already, open up ``Developer Tools`` by pressing ``Ctrl + Shift + i``.
2. Click the ``Select Element`` button at the top left of the new panel. Outlined in red below:

![clickSelectElement](https://user-images.githubusercontent.com/76179807/201521504-7f534a2f-78ad-42ee-a683-f7c985325edc.png)

3. Now that you have clicked ``Select Element`` hover your mouse over the user you want to get the channel ID for. For example, I have labelled the following DM as "test":

![shouldLookLikeThis](https://user-images.githubusercontent.com/76179807/201521521-3c2d8e8f-6cb6-4b4f-967d-81b5015f0f46.png)

You now want to click on their DM in the area marked in green below:

![selectDontSelect](https://user-images.githubusercontent.com/76179807/201521538-0a9b4425-0ba9-4662-808f-859e82857909.png)

``Note``: Don't worry if things don't look exactly the same.

4. You should now have noticed that the panel on the right should have changed and selected some text. If it hasn't, try steps 2 - 3 again. Your panel on the right should look something like the following:

![selectedElement](https://user-images.githubusercontent.com/76179807/201521546-6fc53242-397f-4ade-b3d0-b3f41d0e2d03.png)

``Note``: a few things will be different here for you, but as long as it looks sort of similar, you're on the right track. As long as the selected text starts with ``<a class="``, you're on the right path. If not, try again from steps 2 - 3.

5. On the selected text, right click on it, and choose ``Edit as HTML``, as shown below:

![editAsHTML](https://user-images.githubusercontent.com/76179807/201521561-f68c4ab5-5e15-45bd-b44d-73ec903b3d87.png)

6. Your view on the panel should now look similar to the following:

![hrefToCopy](https://user-images.githubusercontent.com/76179807/201521749-6e7780a1-38ef-4386-82ed-a02bf7c5fd23.png)

Now you need to identify the text that's labelled in a red box.

``Note``: The ending digits past the last ``/`` will be different for you, but as long as you have found this line, you are almost done.

7. All that you have to do now, is copy the final set of numbers in that line of text. Everything excluding the ``/``, and ``"``. So, everything as shown in the green box below:

![channelID](https://user-images.githubusercontent.com/76179807/201521598-9a396b59-88b0-497a-8948-085cda02486c.png)

For me, I should have: ``101010101010101010`` selected.

8. You can now copy that text, and use it in the application when asked for what channel you want to delete from. Once again, not sure why you'd want to do it this way, but you did it!

## Future plans:
Below are some things I consider adding to this app in the future. 
- Command line usage. (Able to call the app ffrom the command line with options)
- ~~An option to delete a certain amount of messages, or simply all of them.~~ - ``Added``
- Support for more operating systems. Right now, this will probably be the easiest to do, as only a few things will need to be changed. 
- ~~A better set of menus. The most important would be showing the user a list of their conversations. The DM they wish to delete messages from could be selected there. Instead of manually retrieving the channel ID themselves.~~ - ``Added``
- Expand on the previously added feature by also giving the option for displaying servers. 

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
