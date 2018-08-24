/***************************************************************************
	> File Name: locker.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年08月24日 星期五 16时57分38秒
 ************************************************************************/
#ifndef LOCKER_H_
#define LOCKER_H_

class ILockObject
{
public:
	virtual ~ILockObject() {}
	virtual void Lock() = 0;
	virtual bool TryLock() = 0;
	virtual void UnLock() = 0;
};

class SpinLock : public ILockObject
{
public:
	SpinLock() { pthread_spin_init(&lock_, PTHREAD_PROCESS_PRIVATE); }
	~SpinLock() { pthread_spin_destroy(&lock_); }

	virtual void Lock() { pthread_spin_lock(&lock_); } 
	virtual bool TryLock() { return pthread_spin trylock(&lock_) == 0; }
	virtual void UnLock() { pthread_spin_unlock(&lock_); }

private:
	pthread_spinlock_t lock_;
};

class MutexLock : public ILockObject
{
public:
	MutexLock() { pthread_mutex_init(&lock_, NULL); }
	~MutexLock() { pthread_mutex_destroy(&lock_); }

	virtual void Lock() { pthread_mutex_lock(&lock); }
	virtual bool TryLock() { return pthread_mutex_trylock(&lock_) == 0; }
	virtual void UnLock() { pthread_mutex_unlock(&lock_); }

private:
	pthread_mutex_t lock_;
};

class Locker
{
public:
	Locker(ILockObject* lock)
	{
		if(lock)
		{
			lock_obj_ = lock;
			lock_obj_->Lock();
		}
	}

	~Locker()
	{
		if(lock_obj_)
		{
			lock_obj_->UnLock();
			lock_obj_ = NULL;
		}
	}

private:
	Locker() {}

private:
	ILockObject* lock_obj_;
}

#endif//LOCKER_H_
