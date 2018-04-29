
struct map{
    unsigned int m_size;
    void *m_addr;
};

void *smalloc(struct map *mp, unsigned int size);
void mfree(struct map *mp, unsigned int size, void *aa);

