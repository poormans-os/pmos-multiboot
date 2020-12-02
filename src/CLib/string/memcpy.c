void memcpy(void *dest, void *src, const size_t n)
{
    // Copy contents of src[] to dest[]
    for (size_t i = 0; i < n; i++)
        ((char *)dest)[i] = ((char *)src)[i];
}