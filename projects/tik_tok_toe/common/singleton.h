#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T>
class Singleton {
  public:
    T* operator->() {
        return mpInstance;
    }
    const T* operator->() const {
        return mpInstance;
    }
    T& operator*() {
        return *mpInstance;
    }
    const T& operator*() const {
        return *mpInstance;
    }

    static T *getInstance() {
        if(m_instance == NULL) {
            m_instance = new T;
        }

        return m_instance;
    }

  private:
    static T *m_instance;
}

#endif // SINGLETON_H
