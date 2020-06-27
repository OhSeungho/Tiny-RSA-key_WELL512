# Tiny-RSA-key_WELL512
Tiny RSA with WELL512 Random number generator C++ Programming

암호시스템에 사용 가능한 의사 난수 생성기를 구현과 구현한 의사 난수 생성기를 사용하여 구성한 암호시스템, 마지막으로 구현된 시스템을 간단하게 공격해 보는 것으로 구성되어있습니다.

의사 난수 생성기는 WELL Random number generator를 구현하였고, 이를 사용한 암호시스템은 RSA 공개키 암호시스템 알고리즘을 활용하였습니다.

RSA 암호체계의 안정성은 큰 숫자를 소인수분해 하는 것이 어렵다는 것에 기반을 두고 있습니다. 이에 Sieve of Eratosthenes를 활용하여 N = p * q에서 N값을 N값을 소인수분해 하는 과정을 구성해 보았습니다.
