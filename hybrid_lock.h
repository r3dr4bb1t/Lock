#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct hybrid_lock_t {

	pthread_mutex_t _m;
	pthread_spinlock_t _s;
}hybrid_lock_t;

//  hybrid_lock_init(

//     pthread_mutex_init(&(lock->_m), NULL);
//     pthread_spin_init(&(lock->_s), 0);
//    );
// int hybrid_lock_destroy(

//    // pthread_mutex_destroy(&(lock->_m));
//    // pthread_spin_destroy(&(lock->_s));
//    );
// int hybrid_lock_lock(

//  //   pthread_mutex_lock(&(lock->_m));
//  //   pthread_spin_lock(&(lock->_s));
// 	);

// int hybrid_lock_unlock(
// 	 // pthread_mutex_unlock(&(lock->_m));
//   //  pthread_spin_unlock(&(lock->_s));
//    );
