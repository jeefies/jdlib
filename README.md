# JDLib
**Author: Jeefy**  
**Email: jeefy163@163.com**  
**Mirror URL: gitee.com/jeefy/jdlib.git**  
**Language: C**

# Typedef
```
typedef void* jany;
typedef char* jstr;
```

# Structures
This is a common use lib for some data structures like List or str\_list.  
Name features is like j\[struct subtype\]\[struct type\]  
> Each main struct can use `->len` to get the length of the structure.
- - -
## JStr
It refers to `char*` (`typedef char* jstr`)
### jstr_copy(jstr src)
return a `jstr` instance allocated by `malloc` method.  
### jstr_free(jstr str)
return NULL and `free(str)` which is allocated by `malloc` or created by `jstr_copy`
- - -
## JStrs
A linear str list. Like what `jllist` do.  
### jstrs\_new(int size)
return a `jstrs *` pointer with some free space allocated according to param `size`.  
### jstrs\_new\_empty()
It's like what `jstrs_new(0)` works.
### jstrs\_new\_from(jstrs strs)
return a new list copied from strs, each item would be allocated by `malloc` again.
### jstrs\_free(jstrs strs)
Each item appended or inserted would be freed, too.  
Free the space of the strs and return NULL.  
### jstrs\_index(jstrs strs, int index)
return the item at `index`.  
If index is negative, return the item from the end of the list.  
If index is invalid (out of range), return NULL.
### jstrs\_print(jstrs strs, jstr sep)
Print the strs to `stdin`, print out sep between each item (no `\n` and sep after last item).  
> For instance, if strs is ["abc", "def"], `jstrs\_print(strs, ",")` would print:  
> `abc,def`
### jstrs\_append(jstrs strs, jany sep)

