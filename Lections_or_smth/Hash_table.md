# Hash - таблица
$f: M -> N$, где н - конечное множество
Для любого $n \in N, \exists x m, f(m) = n$
f - хэш функция, причем не биективная
$\forall data \in M, p = f(data) = f(key)$
хэш = ToDec(str) % size(это количество строк)
## Стандарт IPC (System V)
очередь сообщений (msg)
семафоры (sem)
разделяемая память (shm)
файлы, проецируемые в память
Типы системных вызовов для работы с средствами синхронизации:
1. ... get
2. ... crtl
3. ... op

#### Примеры
```c
int desc;
desc = msgget(150, IPC_CREAT|0760);
struct msgbuf{
  long mtype;
  char mtext[BUFFSIZ];
}
struct msgbuff m;
m.mtype = 1;
m.mtext[0] = "A";
msdsnd(desc, &m,sizemtext, IPC_NOWAIT);


msgtl(int desc, int cmd, struct msgid_ds* pt);
```
