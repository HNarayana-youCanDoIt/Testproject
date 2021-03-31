#!/bin/bash
echo "Setting the qmake path for build"  
source /opt/elina/environment-setup-cortexa9hf-vfp-neon-elina-linux-gnueabi

echo "Setting the sysroot(CMAKE_SYSROOT) to latest sysroot from sdk for the project"

CMAKE_SYSROOT=/opt/elina/sysroots/cortexa9hf-vfp-neon-elina-linux-gnueabi/

cd build



while true; do
	
	read -p "Please give your choice:
	1. Build Only
	2. Clean Build "  choice
	

    if [ "$choice" =  "2" ]
        then
            echo "Doing make distclean"
	
			make distclean
			read -p "Press enter to continue"
	break
	fi

   if [ "$choice" =  "1" ]
	then
          echo "Doing Build only no clean."
	break
	else
	  echo "Wrong Input given By you."

   fi
done



echo "Doing qmake TATA_X445_UnitTest.pro"

qmake ../x451/TATA_X445_UnitTest.pro

echo "Compiling and building the TATA_X445_UnitTest using make -j2"

make -j6

echo "Striping the binaries"

/opt/elina/sysroots/x86_64-elinasdk-linux/usr/bin/arm-elina-linux-gnueabi/arm-elina-linux-gnueabi-strip TMLHMI

echo "Binary Stripped Successfully"

#echo "Copying the binary on Target 10.90.30.165." 

#scp TMLHMI root@10.90.30.165:/opt/hmi/
