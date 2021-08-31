PXCT simulation

Location on fishtank:
cd /mnt/simulations/pxct/lijie/PXCT_Sim/build

1) cmake -DGeant4_DIR=/mnt/simulations/proton_detector/Geant4/geant4.10.2-install/lib/Geant4-10.2.2 /mnt/simulations/pxct/lijie/PXCT_Sim

2) make

3) ./tele vis


Location on my laptop:
VMware Ubuntu can also use these files.

cdp
cd /home/sun/app/PXCT-build

1) cmp
cmake -DGeant4_DIR=/home/sun/app/geant4.10.02-install/lib/Geant4-10.2.3 /mnt/hgfs/PXCT

2) make

3) ./tele vis