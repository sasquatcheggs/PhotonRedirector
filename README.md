This was primarily written by Deepseek.

It hooks and redirects specified addresses.
It was written for PUN redirection, but can be used to redirect other things as well.

LANSettings.txt example:
```
ns.photonengine.com | 127.0.0.1:5058
ns.exitgames.com | 127.0.0.1:5058
ns.photonengine.io | 127.0.0.1:5058
ns.exitgames.io | 127.0.0.1:5058
```

It is recommended to use this alongside PhotonLauncher and LuxonServer.
I plan to add injection to PhotonLauncher, but winmm can be used for now.


Feel free to fork/modify/redistribute this as you please.
