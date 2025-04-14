# Trust Language Lexer

This project is a **Lexical Analyzer (Lexer)** for the `Trust` programming language — a Rust-inspired imperative language.

The lexer reads `.trust` source files and converts them into a stream of tokens, which can later be used for syntax analysis (parsing) and code generation.

---

## 🔥 Features

- Supports **Keywords** (`fn`, `let`, `if`, `return`, `true`, `false`, `loop`, etc.)
- Identifies **Operators** (`+`, `-`, `*`, `/`, `==`, `!=`, `&&`, `||`, `!`, etc.)
- Recognizes **Identifiers** for variable and function names.
- Supports **Decimal** and **Hexadecimal Numbers**.
- Parses **String Literals**.
- Ignores **Comments** starting with `//`.
- Handles **Whitespace** (space, tab, newline).

---

## 🧠 Token Table

| Lexeme       | Token Name         |
|--------------|---------------------|
| `bool`       | `T_Bool`            |
| `break`      | `T_Break`           |
| `continue`   | `T_Continue`        |
| `fn`         | `T_Fn`              |
| `let`        | `T_Let`             |
| `if`         | `T_If`              |
| `return`     | `T_Return`          |
| `true`       | `T_True`            |
| `false`      | `T_False`           |
| `+` `-` `*` `/` `%` | `T_AOp_*` |
| `==` `!=` `<` `>` `<=` `>=` | `T_ROp_*` |
| `&&` `||` `!`  | `T_LOp_*`         |
| `=`           | `T_Assign`         |
| `;`           | `T_Semicolon`      |
| `:`           | `T_Colon`          |
| `->`          | `T_Arrow`          |
| Strings like `"..."` | `T_String`  |
| Comments `//...` | `T_Comment`    |
| Whitespace | `T_Whitespace` |

---

## 🚀 Usage

1. Clone the repository:
```bash
git clone https://github.com/your-username/trust-lexer.git
cd trust-lexer
