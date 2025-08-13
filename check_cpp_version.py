import re
import pathlib

# Расширенный список фич (шаблон, версия C++)
features = [
    # C++11
    (r"\bnullptr\b", 11),
    (r"\bauto\b\s+\w+\s*=", 11),
    (r"\[\s*\]\s*\(", 11),  # lambda
    (r"\bconstexpr\b", 11),
    (r"static_assert\s*\(", 11),
    (r"std::unique_ptr", 11),
    (r"std::shared_ptr", 11),
    (r"override\b", 11),
    (r"final\b", 11),
    (r"enum\s+class", 11),
    (r"noexcept", 11),
    (r"=delete", 11),
    (r"=default", 11),

    # C++14
    (r"0b[01]+", 14),
    (r"std::make_unique", 14),
    (r"\[\[deprecated\]\]", 14),
    (r"decltype\(auto\)", 14),
    (r"auto\s+[^=]+\s*=\s*\[", 14),  # generic lambda capture init
    (r"constexpr\s+.*\{", 14),       # relaxed constexpr

    # C++17
    (r"if\s+constexpr", 17),
    (r"auto\s*\[.*\]\s*=", 17),  # structured bindings
    (r"inline\s+namespace", 17),
    (r"std::optional", 17),
    (r"std::variant", 17),
    (r"std::any", 17),
    (r"std::string_view", 17),
    (r"std::filesystem", 17),
    (r"\[\[nodiscard\]\]", 17),
    (r"\bconstexpr\b.*if", 17),  # constexpr if

    # C++20
    (r"\bconcept\b", 20),
    (r"\brequires\b", 20),
    (r"std::ranges", 20),
    (r"\bco_await\b", 20),
    (r"\bco_yield\b", 20),
    (r"\bco_return\b", 20),
    (r"\bconsteval\b", 20),
    (r"\bconstinit\b", 20),
    (r"\bmodule\b", 20),
    (r"\bimport\b", 20),

    # C++23
    (r"std::expected", 23),
    (r"std::print", 23),
    (r"std::move_only_function", 23),
]

min_version = 98
versions_found = set()

print("Проверка файлов проекта...\n")

for path in pathlib.Path(".").rglob("*"):
    if path.suffix.lower() not in (".cpp", ".hpp", ".h", ".cc"):
        continue
    print(f"[Файл] {path}")
    try:
        text = path.read_text(encoding="utf-8")
    except:
        print("  ! Ошибка чтения файла")
        continue

    for pattern, version in features:
        if re.search(pattern, text):
            min_version = max(min_version, version)
            versions_found.add(version)

print("\n--- Результат ---")
if min_version == 98:
    print("Код совместим даже с C++98 (нет фич новее).")
else:
    print(f"Минимальная требуемая версия: C++{min_version}")
    supported_versions = [v for v in (11, 14, 17, 20, 23) if v >= min_version]
    print("Совместим также с версиями:", ", ".join(f"C++{v}" for v in supported_versions))
