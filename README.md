# PhotonRedirector
This was primarily written by Deepseek.

It hooks and redirects specified addresses.
It was written for PUN (Photon Unity Networking) redirection, but can be used to redirect other things as well.

## Usage:

It is recommended to use this alongside [PhotonLauncher](https://github.com/sasquatcheggs/PhotonLauncher) and [LuxonServer](https://github.com/niansa/LuxonServer).  
PhotonLauncher can inject this into games, but a proxy dll or other injection method can be used.  

Addresses to redirect should be defined in a file called ***LANSettings.txt***.

`LANSettings.txt` example:
```
ns.photonengine.com | 127.0.0.1:5058
ns.exitgames.com | 127.0.0.1:5058
ns.photonengine.io | 127.0.0.1:5058
ns.exitgames.io | 127.0.0.1:5058
```

