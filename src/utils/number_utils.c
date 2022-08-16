int is_odd(int num)
{
    return (num % 2 != 0);
}

int is_even(int num)
{
    return !is_odd(num);
}