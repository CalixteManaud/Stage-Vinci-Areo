Partie code en python version 0.1 alpha 0
=====================================

.. contents::

Information général
-------------------
- Code: https://github.com/CalixteManaud/Stage-Vinci-Areo/tree/main/Python
- Wiki: https://github.com/CalixteManaud/Stage-Vinci-Areo/wiki

Utilisation de python
---------------------

Des packets sont déjà préinstallés et d'autres sont disponibles dans le site `https://www.python.org/`.

Les fichiers
------------

Chaque sont différents par rapport aux autres, ils se différencient sur quel composants du cokpit qui est mise sous système.
Exemple:: 

   MCDU 
   FCU 
   OVERHEAD PANEL 
   PEDESTAL...

Description d'un composant
^^^^^^^^^^^^^^^^^^^^^^^^^^

Chaque pièces du cokpit dés qu'li est branché sur un ordinateur doit être anaylsé, lire et écrire. Pour ce faire nous devons tout d'abord avoir sa ``description complète`` de cette pièce, un des fichiers permet de faire ceci, `GetDescriptor <https://github.com/CalixteManaud/Stage-Vinci-Areo/blob/main/Python/getDescriptor.py>`_. Il permet tout simplement de nous donner les informations importantes sur cette pièce comme l'entrée pour lire, la sortie pour écrire...
Voici la descriptiion du OVERHEAD PANEL::

   CONFIGURATION 1: 200 mA ==================================
   bLength              :    0x9 (9 bytes)
   bDescriptorType      :    0x2 Configuration
   wTotalLength         :   0x27 (39 bytes)
   bNumInterfaces       :    0x1
   bConfigurationValue  :    0x1
   iConfiguration       :    0x0 
   bmAttributes         :   0xc0 Self Powered
   bMaxPower            :   0x64 (200 mA)
      ENDPOINT 0x1: Bulk OUT ===============================
       bLength          :    0x7 (7 bytes)
       bDescriptorType  :    0x5 Endpoint
       bEndpointAddress :    0x1 OUT
       bmAttributes     :    0x2 Bulk
       wMaxPacketSize   :   0x40 (64 bytes)
       bInterval        :    0x1
      ENDPOINT 0x81: Bulk IN ===============================
       bLength          :    0x7 (7 bytes)
       bDescriptorType  :    0x5 Endpoint
       bEndpointAddress :   0x81 IN
       bmAttributes     :    0x2 Bulk
       wMaxPacketSize   :   0x40 (64 bytes)
       bInterval        :    0x1
      ENDPOINT 0x82: Interrupt IN ==========================
       bLength          :    0x7 (7 bytes)
       bDescriptorType  :    0x5 Endpoint
       bEndpointAddress :   0x82 IN
       bmAttributes     :    0x3 Interrupt
       wMaxPacketSize   :   0x40 (64 bytes)
       bInterval        :    0x1
   DEVICE ID 04d8:0070 on Bus 001 Address 031 =================
       bLength                :   0x12 (18 bytes)
       bDescriptorType        :    0x1 Device
       bcdUSB                 :  0x200 USB 2.0
       bDeviceClass           :    0x0 Specified at interface
       bDeviceSubClass        :    0x0
       bDeviceProtocol        :    0x0
       bMaxPacketSize0        :    0x8 (8 bytes)
       idVendor               : 0x04d8
       idProduct              : 0x0070
       bcdDevice              :    0x0 Device 0.0
       iManufacturer          :    0x1 Error Accessing String
       iProduct               :    0x2 Error Accessing String
       iSerialNumber          :    0x0 
       bNumConfigurations     :    0x1
      
Et le code qui permet de d'afficher la description:

.. code-block:: python
    
    for cfg in dev:
    print(cfg._get_full_descriptor_str())
    for i in cfg:
        for e in i:
            print(e.__str__())

    print(dev._get_full_descriptor_str())

MCDU
^^^^

Le ``MCDU`` permet d'aider le(s) pilote(s) pendant le vol en fournissant des renseignements sur le pilotatge, la navigation, la consommation de carburant, etc. Il présent sur plusieurs appareils (Avions de ligne, hélicoptère..). Poour en savoir plus, voici le `lien <https://fr.wikipedia.org/wiki/Fichier:CP_MCDU.jpg>`_.

Deux fichiers importants sont utilisés pour le MCDU, `MCDU_Descriptor <https://github.com/CalixteManaud/Stage-Vinci-Areo/blob/main/Python/MCDU_descriptor.py>`_, qui fait d'office de nous donner les informations entrées et le `test_MCDU_input <https://github.com/CalixteManaud/Stage-Vinci-Areo/blob/main/Python/test_MCDU_input.py>`_, qui permet de nous qu'elle bouton est appuyé depuis l'ordinateur. Voici un extrait de ce qui sort lors d'une touche appuyé::
    
    la touche A   appuyé
    Button        relaché
    la touche SP  appuyé
    Button        relaché
    
Pour obtenir à ce résultat, il faut convertir les données reçus par l'usb (``en binaire -> integer``), ce procéder nous pense difficile mais avec un peu de logique nous découvrons que cela est facile. Un extrait du code qui permet ce résultat:

.. code-block:: python
   
        data = dev.read(0x82, 4, 5000)

        b = bin((data[1] & ~(1 << 6)) >> 1)
        groupe = int(b, 2)

        byte1 = ~(data[2]) & 255
        byte1 = (byte1 & -byte1)
        byte1 = 0 if byte1 == 0 else log((byte1 & -byte1), 2) + 1
        byte1 = int(byte1)
        
