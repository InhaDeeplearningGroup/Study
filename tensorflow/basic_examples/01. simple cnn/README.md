# 01. Simple cnn model

tensorflow를 이용한 간단한 CNN model 예제입니다.

데이터 셋은 CIFAR-10 데이터 셋을 사용하였습니다. 

(SVHN 데이터 셋 생성 및 tfrecord 변환 파일 추가)

데이터 셋을 생성하기 위해서는 아래 파이썬 파일을 실행시키면 됩니다.
> python cifar10_full.py

> python svhn_full.py

./dataset/cifar\ 10/seed1/에 tfrecord 형식의 데이터 파일을 확인하실 수 있습니다.

네트워크 학습은 간단하게 아래 파이썬 파일을 실행시키면 됩니다.
> python simple_cnn.py

다음 파일에는 많은 option이 존재합니다.

따라서 아래와 같이 실행시켜서 원하는 hyperparameter를 수정하시기 바랍니다.

> python simple_cnn.py --help
 
다음 예제는 아래의 깃허브 주소의 소스 코드를 참고하였습니다.

"https://github.com/takerum/vat_tf"