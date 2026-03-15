# 🖼️ Image Processor

Консольное приложение и GUI для обработки изображений в формате BMP.

## Возможности

### Фильтры
| Фильтр | Команда | Параметры |
|--------|---------|-----------|
| Grayscale | `-gs` | — |
| Negative | `-neg` | — |
| Sharpening | `-sharp` | — |
| Edge Detection | `-edge` | `threshold` (0.0–1.0) |
| Gaussian Blur | `-blur` | `sigma` |
| Crop | `-crop` | `width height` |
| Twirl | `-twirl` | `angle radius` |

### GUI
Графический интерфейс с предпросмотром, выбором фильтров и сохранением результата.

## Установка и сборка

### Требования
- CMake 3.15+
- C++17
- Python 3.x + Pillow, customtkinter (для GUI)

### Сборка C++
```bash
mkdir build && cd build
cmake ..
make image_processor
```

### Запуск GUI
```bash
python3 gui.py
```

## Использование (CLI)

```bash
./image_processor <input.bmp> <output.bmp> [фильтры...]
```

### Примеры
```bash
# Перевести в оттенки серого
./image_processor input.bmp output.bmp -gs

# Размытие + негатив
./image_processor input.bmp output.bmp -blur 2.0 -neg

# Цепочка фильтров
./image_processor input.bmp output.bmp -crop 800 600 -gs -edge 0.2
```

## Поддерживаемые форматы

- Входной формат: 24-битный BMP (без сжатия)
- GUI поддерживает: JPG, PNG, BMP (конвертация автоматическая)
- Выходной формат: PNG, JPG, BMP

## Сборка приложения

Готовые сборки генерируются автоматически через GitHub Actions при пуше в `main`.

Скачать можно во вкладке **Actions → последний билд → Artifacts**.

## Структура проекта

```
├── src/
│   ├── image_processor.cpp    # точка входа
│   ├── color.h                # структура цвета
│   ├── image.h / image.cpp    # класс изображения
│   ├── bmp.h / bmp.cpp        # чтение и запись BMP
│   ├── filter.h               # базовый класс фильтра
│   ├── grayscale_filter.*     # фильтр grayscale
│   ├── negative_filter.*      # фильтр negative
│   ├── sharpening_filter.*    # фильтр sharpening
│   ├── edgedetection_filter.* # фильтр edge detection
│   ├── crop_filter.*          # фильтр crop
│   ├── gaussianblur_filter.*  # фильтр gaussian blur
│   ├── twirl_filter.*         # фильтр twirl (доп.)
│   └── arg_parser.*           # парсер аргументов
├── gui.py                     # графический интерфейс
├── CMakeLists.txt
├── test_script/               # тестовые данные
└── .github/workflows/         # GitHub Actions
```
