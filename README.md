# Keyboard Automation System 🧠⌨️

An interactive C++ project that simulates a keyboard input system with intelligent auto-complete suggestions using Trie data structure and designed with object-oriented principles.

---

## 🚀 Features

- ✅ Real-time sentence building as user types character by character.
- ✅ Returns up to **3 lexicographically smallest suggestions** for the current word.
- ✅ Allows **selection of suggestions**, updating the sentence accordingly.
- ✅ Fully **modular design** using interfaces and OOP patterns for extensibility.

---

## 🛠️ Tech Stack

- **Language:** C++  
- **Design Principles:** OOP
- **Core Data Structure:** Trie  
- **Build Tool:** g++, Makefile (optional)

## 🧪 How It Works

1. **Type a character** → Sentence is updated.
2. **Auto-complete engine** suggests up to 3 possible words matching the current prefix.
3. **User selects a suggestion** → Sentence updates by replacing the current incomplete word.


## 🖼️ Example

```cpp
Typed: m
Suggestions: mobile model monitor

Typed: mo
Suggestions: mobile model monitor

Selected: monitor
Updated Sentence: monitor 
