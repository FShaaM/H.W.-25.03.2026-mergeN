//  Задача.Продумать интерфейс шаблонов точки зрения безопасности относительно исключений и реализовать их

//  Вариант III.Шаблон mergeN

//  Исправить интерфейс при необходимости.Описать неявный интерфейс

//  1. Реализовать шаблоны в том виде, в котором они заданы. Проанализировать реализацию с точки зрения безопасности
//  2. Внести исправления - в том числе в сигнатуру, если необходимо - и предоставить безопасную реализацию

//  Спойлер : нужно будет делать базовую гарантию, поэтому сигнатуру менять в любом случае

//  III. Сливает несколько диапазонов (Каждый со своими размерами) в другой отсортированный диапазон.
//       Возвращает указатель за последний элемент в массиве с результатами c


template< class T >
T* mergeN(const T* const* a, size_t sa, const size_t* sai, T* c)
{
	size_t s = 0;
	for (size_t i = 0; i < sa; ++i)
	{
		s += sai[i];
	}

	const T** ptr_head = new const T*[sa];;
	const T** ptr_tail = nullptr;
	try
	{
		ptr_tail = new const T * [sa];
	}
	catch (std::bad_alloc&)
	{
		delete[] ptr_head;
		throw;
	}

	for (size_t i = 0; i < sa; ++i)
	{
		ptr_head[i] = a[i];
		ptr_tail[i] = a[i] + sai[i];
	}

	for (size_t i = 0; i < s; ++i)
	{
		const T* min_ptr = nullptr;
		size_t min_id = 0;

		for (size_t j = 0; j < sa; ++j)
		{
			if (ptr_head[j] != ptr_tail[j])
			{
				if (!min_ptr)
				{
					min_ptr = ptr_head[j];
					min_id = j;
				}
				else
				{
					if (*min_ptr > *ptr_head[j])                                    // Оператор сравнения (Может кидать исключения)
					{
						min_ptr = ptr_head[j];
						min_id = j;
					}
				}
			}
		}

		c[i] = *min_ptr;                                                           // Оператор копирующего присваивания (Может кидать исключения)
		ptr_head[min_id]++;
	}

	delete[] ptr_head;
	delete[] ptr_tail;

	return (c + s);
}




int main()
{}
