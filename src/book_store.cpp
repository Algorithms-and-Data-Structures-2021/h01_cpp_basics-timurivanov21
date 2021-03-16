#include "book_store.hpp"

#include <algorithm>  // copy
#include <stdexcept>  // invalid_argument

// 1. реализуйте функцию ...
ResizeStorageStatus resize_storage(Book *&storage, int size, int new_capacity) {
  // здесь мог бы быть ваш разносторонний и многогранный код ...
  // Tip 1: проведите валидацию аргументов функции
  if (storage == nullptr) return ResizeStorageStatus::NULL_STORAGE;
  if (size >= new_capacity) return ResizeStorageStatus::INSUFFICIENT_CAPACITY;
  if (size < 0) return ResizeStorageStatus::NEGATIVE_SIZE;
  // Tip 2: не забудьте высвободить ранее выделенную память под хранилище

  Book *new_storage = new Book[new_capacity]{};
  for (int i = 0; i < size; i++) {
      new_storage[i] = storage[i];
  }

  delete storage;
  storage = new_storage;

  return ResizeStorageStatus::SUCCESS;
}

// 2. реализуйте конструктор ...
BookStore::BookStore(const std::string &name) : name_{name} {
  // валидация аргумента
  if (name.empty()) {
    throw std::invalid_argument("BookStore::name must not be empty");
  }
  else {
      // здесь мог бы быть ваш сотрясающий землю и выделяющий память код ...
      storage_capacity_ = kInitStorageCapacity;
      storage_ = new Book[kInitStorageCapacity]{};
      storage_size_ = 0;
      name_ = name;
  }
}

// 3. реализуйте деструктор ...
BookStore::~BookStore() {
    delete storage_;
    storage_ = nullptr;
    storage_size_ = 0;
    storage_capacity_ = 0;
  // здесь мог бы быть ваш высвобождающий разум от негатива код ...
  // Tip 1: я свободен ..., словно память в куче: не забудьте обнулить указатель
}

// 4. реализуйте метод ...
void BookStore::AddBook(const Book &book) {
  if (storage_size_ == storage_capacity_) {
    // здесь мог бы быть ваш умопомрачительный код ...
    // Tip 1: используйте функцию resize_storage_internal, задав новый размер хранилища
    ResizeStorageStatus storage_status = resize_storage_internal(storage_capacity_ + kCapacityCoefficient);
    if (storage_status != ResizeStorageStatus::SUCCESS){
        return;
    }
    // Tip 2: не забудьте обработать статус вызова функции
  }
  // Tip 3: не забудьте добавить книгу в наше бездонное хранилище ...
    storage_[storage_size_] = book;
    storage_size_++;
}

// РЕАЛИЗОВАНО

const std::string &BookStore::GetName() const {
  return name_;
}

int BookStore::GetSize() const {
  return storage_size_;
}

int BookStore::GetCapacity() const {
  return storage_capacity_;
}

const Book *BookStore::GetBooks() const {
  return storage_;
}

ResizeStorageStatus BookStore::resize_storage_internal(int new_capacity) {
  // изменяем размеры хранилища с копированием старых данных в хранилище нового объема
  const ResizeStorageStatus status = resize_storage(storage_, storage_size_, new_capacity);

  // если все прошло ОК, то сохраняем новый объем хранилища в объекте
  if (status == ResizeStorageStatus::SUCCESS) {
    storage_capacity_ = new_capacity;
  }

  return status;
}