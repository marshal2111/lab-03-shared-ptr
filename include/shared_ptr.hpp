// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_SHARED_PTR_HPP_
#define INCLUDE_SHARED_PTR_HPP_

#include <atomic>
#include <cstddef>

auto example() -> void;

template <typename T>
class SharedPtr {
private:
    T* obj = nullptr;
    std::atomic_uint* refCount = nullptr;

public:
    SharedPtr() {
        obj = nullptr;
        refCount = new std::atomic_uint{0};
    }
    explicit SharedPtr(T* ptr) {
        obj = ptr;
        refCount = new std::atomic_uint{1};
    }
    SharedPtr(const SharedPtr& r) {
        obj = r.obj;
        refCount = r.refCount;
        if (r.obj != nullptr) {
    	    (*refCount)++;
        }
    }
    SharedPtr(SharedPtr&& r) {
        obj = std::move(r.obj);
        refCount = std::move(r.refCount);
    }
    ~SharedPtr() {
        if (*refCount > 0) {
    	    (*refCount)--;
        }
        if (*refCount == 0) {
    	    delete obj;
    	    obj = nullptr;
    	    delete refCount;
    	    refCount = nullptr;
        }
    }

    auto operator=(const SharedPtr& r) -> SharedPtr& {
        if (obj != r.obj) {
    	    if (*refCount > 0) {
    		    (*refCount)--;
    	    }
    	    if (*refCount == 0) {
    		    delete obj;
    		    obj = nullptr;
    		    delete refCount;
    		    refCount = nullptr;
    	    } 
    	    refCount = r.refCount;
    	    obj = r.obj;
    	    if (r.obj != nullptr) {
    		    (*refCount)++;
    	    }
        }
        return *this;
    }
    auto operator=(SharedPtr&& r) -> SharedPtr& {
        if (obj != r.obj) {
    	    if (*refCount > 0) {
    	        (*refCount)--;
    	    }
    	    if (*refCount == 0) {
    		    delete obj;
    		    obj = nullptr;
    		    delete refCount;
    		    refCount = nullptr;
    		}
    	    obj = std::move(r.obj);
    	    refCount = std::move(r.refCount);
        }
        return *this;
    }

    // проверяет, указывает ли указатель на объект
    operator bool() const {
    	return obj != nullptr;
    }
    auto operator*() const -> T& {
    	return obj;
    }
    auto operator->() const -> T* {
    	return obj;
    }

    auto get() -> T* {
    	return obj;
    }
    void reset() {
    	if (*refCount > 0) {
    		(*refCount)--;
    	}
    	if (*refCount == 0) {
    		delete obj;
    		obj = nullptr;
    		delete refCount;
    		refCount = nullptr;
    	}
    	obj = nullptr;
    	refCount = new std::atomic_uint{0};
    }
    void reset(T* ptr) {
    	if (*refCount > 0) {
    		(*refCount)--;
    	}
    	if (*refCount == 0) {
    		delete obj;
    		obj = nullptr;
    		delete refCount;
    		refCount = nullptr;
    	}
    	obj = ptr;
    	refCount = new std::atomic_uint{1};
    }
    void swapPtr(SharedPtr& r) {
    	T* tmp_obj = obj;
    	std::atomic_uint* tmp_count = refCount;
    	obj = r.obj;
    	refCount = r.refCount;
    	r.obj = tmp_obj;
    	r.refCount = tmp_count;
    }
    auto use_count() const -> size_t {
    	if (refCount == nullptr){
    		return 0;
    	} else {
    		return *refCount;
    	}
    }
};

#endif // INCLUDE_SHARED_PTR_HPP_
