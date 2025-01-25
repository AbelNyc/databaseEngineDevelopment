# Database Engine Development

## Progress Update
### **Current Status:**
We have successfully implemented a basic **file-based storage system** using `fstream` for reading and writing structured data in **binary format**.

### **What We Learned Today**
#### **1️⃣ Understanding `fstream` and Binary File I/O**
✅ **`seekp(0, std::ios::end);`** → Moves the write pointer to the **end of the file** to avoid overwriting existing data.  
✅ **`write(reinterpret_cast<const char*>(&row), RECORD_SIZE);`** → Writes **raw binary data** to the file.  
✅ **`flush();`** → Forces the OS to write buffered data **immediately to disk** to prevent data loss.  

#### **2️⃣ Why File Writes Are Slow**
🔹 **Disk I/O is the bottleneck** because data moves from **RAM to disk**, which is much slower than memory operations.  
🔹 **Frequent `write()` and `flush()` calls** slow things down due to multiple system calls.  
🔹 **OS buffering helps**, but explicit writes still add overhead.  

#### **3️⃣ How `mmap()` Can Improve Performance (But Not Implemented Yet)**
✅ **Direct memory access** instead of `seekp()`, `write()`, `flush()`.  
✅ **Avoids unnecessary system calls**, making it much faster.  
✅ **Bulk inserts and updates are instant**, since modifications happen in memory.  

### **Next Steps**
🔹 **Implement `mmap()` for direct memory-mapped file storage.**  
🔹 **Optimize indexing (B-Tree or Hash Index) for faster lookups.**  
🔹 **Build a SQL-like Query Parser to support structured queries.**  

### **Pending Implementation:**
🚨 **`mmap()` is not yet implemented!** The next step will be transitioning from `fstream` to **memory-mapped files** to improve performance.  

---

### **Project Overview**
#### **Current Features:**
✅ **Binary file storage using `fstream`**
✅ **CRUD operations (Insert, Select, Update, Remove)**
✅ **Soft delete (marking rows as deleted instead of removing them)**

#### **Planned Features:**
🔹 **Memory-mapped file support (`mmap()`)**
🔹 **Indexing for optimized queries (B-Tree or Hash Index)**
🔹 **SQL-like query execution**
🔹 **Concurrency support for multi-threaded access**

---
**Stay tuned for further updates as we transition to a high-performance database engine! 🚀**

