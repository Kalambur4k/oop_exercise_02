# Отчёт по лабораторной работе
## Генеративные текстовые нейросети
## Вариант 8
### Студенты: 

| ФИО       | Роль в проекте                     | Оценка       |
|-----------|------------------------------------|--------------|
|Прудникова А.А.  | Программировал SimpleRNN модели и создание генерирующей сети |       |
|Клитная А.В.  | Программировал LSTM модели |      |
|Ивченко А.В.  | Программировал LSTM модели |      |
|Велесов Д.И.  | Писал отчёт/Программировал SimpleRNN |          |

> *Комментарии проверяющего*

## Датасет

В качестве датасета командой были выбраны Субтитры фильмов.Команде показалось использование датасета практичным и интересным в рамках выполнения данной лабораторной работы. В качестве исходных данных используются цитаты из различных фильмов, а в качестве результата - оригинальный дубляж.
## SimpleRNN

Создаётся простая нейросеть с одним слоем SimpleRNN, но перед этим vectorizer, который обрабатывает массив строк или тензоры и делит их на символы или слова через пробелы в зависимости от параметра split. 

```python
vectorizer = tf.keras.layers.TextVectorization(split='character')

print('Training vectorizer')
vectorizer.adapt(list(train["overview"]))
```

Используется embedding для сжатия, так как размер словаря для целых слов будет очень большим, а его использование позволяет экономить память.

```python
model = keras.Sequential()
model.add(vectorizer)
model.add(layers.Embedding(input_dim=100000, output_dim=64, mask_zero=True))
model.add(layers.SimpleRNN(4))
model.add(layers.Dense(100, activation = 'tanh'))
model.summary()
```

Обучаем нашу нейросеть. Параметры были подобраны особым образом, для исключения ситуации, где нейросеть выбирает единственный класс для сопоставления:

```python
model.compile(keras.optimizers.Adam(0.01), keras.losses.SparseCategoricalCrossentropy(from_logits=True), ['acc'])
train_model = model.fit(x=x, y=y, batch_size=64, epochs = 10, validation_data=(test_x, test_y))
```

## LSTM

LSTM является более комлпексной моделью, поэтому её обучение даёт большую точность. Подготовка происходит аналогичным способом

Была реализована однослойная однонаправленная модель:

```python
model = keras.Sequential()
model.add(vectorizer)
model.add(layers.Embedding(input_dim=40000, output_dim=8, mask_zero=True))
model.add(layers.LSTM(4))
model.add(layers.Dense(100, activation = 'tanh'))
model.summary()
```

Двуслойная однонаправленная модель, для неё мы передаём из LSTM все промежуточные результаты в следующий слой:

```python
model = keras.Sequential()
model.add(vectorizer)
model.add(layers.Embedding(input_dim=40000, output_dim=64, mask_zero=True))
model.add(layers.LSTM(8, return_sequences=True))
model.add(layers.LSTM(4))
model.add(layers.Dense(100, activation = 'tanh'))
model.add(layers.Dense(100, activation = 'tanh'))
model.summary()
```

Двунаправленная LSTM-модель с одним слоем:

```python
model = keras.Sequential()
model.add(vectorizer)
model.add(layers.Embedding(input_dim=40000, output_dim=16, mask_zero=True))
model.add(layers.Bidirectional(keras.layers.LSTM(8), merge_mode='concat')),
model.add(layers.Dense(100, activation = 'tanh'))
model.summary()
```

Параметры слоёв регулировались вручную, исходя из результатов обучения при тех или иных параметрах.

## Трансформерная архитектура

Для создания трансформерной архитектуры использовалась библиотека keras_nlp, которая позволяет разбивать тензоры строк на токены из слов. После мы производим преобразование с последующим созданием модели, и начинаем обучать нашу нейросеть:

```python
inputs = keras.layers.Input(shape=(None,), dtype=tf.int32)
# Embedding.
embedding_layer = keras_nlp.layers.TokenAndPositionEmbedding(
    vocabulary_size=VOCAB_SIZE,
    sequence_length=SEQ_LEN,
    embedding_dim=EMBED_DIM,
    mask_zero=True,
)
x = embedding_layer(inputs)
# Transformer decoders.
for _ in range(NUM_LAYERS):
    decoder_layer = keras_nlp.layers.TransformerDecoder(
        num_heads=NUM_HEADS,
        intermediate_dim=FEED_FORWARD_DIM,
    )
    x = decoder_layer(x)  # Giving one argument only skips cross-attention.
# Output.
outputs = keras.layers.Dense(VOCAB_SIZE)(x)
model = keras.Model(inputs=inputs, outputs=outputs)
loss_fn = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True)
perplexity = keras_nlp.metrics.Perplexity(from_logits=True, mask_token_id=0)
model.compile(optimizer="adam", loss=loss_fn, metrics=['acc'])
```

После обучения мы можем использовать обратный вызов нашей модели для генерации текстов:

```python3
class TopKTextGenerator(keras.callbacks.Callback):
    """A callback to generate text from a trained model using top-k."""

    def __init__(self, k):
        self.sampler = keras_nlp.samplers.TopKSampler(k)

    def on_epoch_end(self, epoch, logs=None):
        output_tokens = self.sampler(
            next=next,
            prompt=prompt_tokens,
            index=1,
        )
        txt = tokenizer.detokenize(output_tokens)
        print(f"Top-K search generated text: \n{txt}\n")


text_generation_callback = TopKTextGenerator(k=10)
# Dummy training loop to demonstrate callback.
model.fit(train_ds, verbose=2, epochs=10, callbacks=[text_generation_callback])
```

