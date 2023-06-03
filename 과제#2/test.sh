#!/bin/zsh
# 파일 명
NAME="strong"
DEFAULT_TEST_NUM=3
TEST_NUM=100
COMPILE=g++

./fclean.sh

mkdir myInput/
mkdir myOutput/

echo "
=============================================================================================================================

  :::::::::::       ::::::::::       ::::::::   :::::::::::       ::::::::::       :::::::::
     :+:           :+:             :+:    :+:      :+:           :+:              :+:    :+:
    +:+           +:+             +:+             +:+           +:+              +:+    +:+
   +#+           +#++:++#        +#++:++#++      +#+           +#++:++#         +#++:++#:
  +#+           +#+                    +#+      +#+           +#+              +#+    +#+
 #+#           #+#             #+#    #+#      #+#           #+#              #+#    #+#
###           ##########       ########       ###           ##########       ###    ###

      ::::::::::       ::::::::       :::::::::
     :+:             :+:    :+:      :+:    :+:
    +:+             +:+    +:+      +:+    +:+
   :#::+::#        +#+    +:+      +#++:++#:
  +#+             +#+    +#+      +#+    +#+
 #+#             #+#    #+#      #+#    #+#
###              ########       ###    ###

      :::        :::::::::::       :::    :::       ::::::::::        :::        :::::::::::       ::::::::       ::::    :::
     :+:            :+:           :+:   :+:        :+:               :+:            :+:          :+:    :+:      :+:+:   :+:
    +:+            +:+           +:+  +:+         +:+               +:+            +:+          +:+    +:+      :+:+:+  +:+
   +#+            +#+           +#++:++          +#++:++#          +#+            +#+          +#+    +:+      +#+ +:+ +#+
  +#+            +#+           +#+  +#+         +#+               +#+            +#+          +#+    +#+      +#+  +#+#+#
 #+#            #+#           #+#   #+#        #+#               #+#            #+#          #+#    #+#      #+#   #+#+#
########## ###########       ###    ###       ##########        ########## ###########       ########       ###    ####

=============================================================================================================================
- made by 김민석
"

echo  "\n#################### compile ####################\n"
${COMPILE} ${NAME}.cpp -o ${NAME}
if [ ! -f "$NAME" ]; then
	echo "[Error] $NAME.cpp 파일이 없습니다!"
	exit(128)
fi

${COMPILE} make_test.cpp -o make_test

echo  "\n#################### default test ####################"
for num in {1..${DEFAULT_TEST_NUM}}
do
	echo "\n--------------------\n"
	echo "test${num}.txt :"
	cat ./defaultTest/test${num}.txt
	echo "\nyour answer :"
	./${NAME} < ./defaultTest/test${num}.txt
	echo "real answer :"
	./validator < ./defaultTest/test${num}.txt
done

echo "\n#################### make ${TEST_NUM} cases ####################\n"
./make_test ${TEST_NUM}

echo "\n#################### test ${TEST_NUM} cases ####################\n"

echo "excute your ${NAME}"
for num in {1..${TEST_NUM}}
do
	echo -ne '['
	for i in {1..${num}}
	do
		echo -ne '#'
	done

	for i in {${num}..100}
	do
		echo -ne ' '
	done
	echo -ne "(${num}%)]\r"

	./${NAME} < ./myInput/myInput${num}.txt >> ./myOutput/${NAME}_log${num}.txt
done

echo "\nexcute validator"
for num in {1..${TEST_NUM}}
do
	echo -ne '['
	for i in {1..${num}}
	do
		echo -ne '#'
	done
	for i in {${num}..100}
	do
		echo -ne ' '
	done
	echo -ne "(${num}%)]\r"

	./validator < ./myInput/myInput${num}.txt >> ./myOutput/validator_log${num}.txt
done

echo "\ncheck your result"
for num in {1..${TEST_NUM}}
do
	echo -ne '['
	for i in {1..${num}}
	do
		echo -ne '#'
	done
	for i in {${num}..100}
	do
		echo -ne ' '
	done
	echo -ne "(${num}%)]\r"

	echo "<<= ${num} =>>" >> ./diff_log.txt
	diff ./myOutput/${NAME}_log${num}.txt ./myOutput/validator_log${num}.txt >> ./diff_log.txt
done

echo "\n\ncheck time complexity"
time ./${NAME} < ./bigInput/input1.txt
time ./${NAME} < ./bigInput/input2.txt
time ./${NAME} < ./bigInput/input3.txt
time ./${NAME} < ./bigInput/input4.txt
time ./${NAME} < ./bigInput/input5.txt

echo "\n==================== diff_log.txt ===================="
cat diff_log.txt
