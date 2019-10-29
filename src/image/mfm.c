/*
 * mfm.c
 * 
 * MFM-conversion tables and routines.
 * 
 * Written & released by Keir Fraser <keir.xen@gmail.com>
 * 
 * This is free and unencumbered software released into the public domain.
 * See the file COPYING for more details, or visit <http://unlicense.org>.
 */

const uint16_t mfmtab[] = {
    0xaaaa, 0xaaa9, 0xaaa4, 0xaaa5, 0xaa92, 0xaa91, 0xaa94, 0xaa95, 
    0xaa4a, 0xaa49, 0xaa44, 0xaa45, 0xaa52, 0xaa51, 0xaa54, 0xaa55, 
    0xa92a, 0xa929, 0xa924, 0xa925, 0xa912, 0xa911, 0xa914, 0xa915, 
    0xa94a, 0xa949, 0xa944, 0xa945, 0xa952, 0xa951, 0xa954, 0xa955, 
    0xa4aa, 0xa4a9, 0xa4a4, 0xa4a5, 0xa492, 0xa491, 0xa494, 0xa495, 
    0xa44a, 0xa449, 0xa444, 0xa445, 0xa452, 0xa451, 0xa454, 0xa455, 
    0xa52a, 0xa529, 0xa524, 0xa525, 0xa512, 0xa511, 0xa514, 0xa515, 
    0xa54a, 0xa549, 0xa544, 0xa545, 0xa552, 0xa551, 0xa554, 0xa555, 
    0x92aa, 0x92a9, 0x92a4, 0x92a5, 0x9292, 0x9291, 0x9294, 0x9295, 
    0x924a, 0x9249, 0x9244, 0x9245, 0x9252, 0x9251, 0x9254, 0x9255, 
    0x912a, 0x9129, 0x9124, 0x9125, 0x9112, 0x9111, 0x9114, 0x9115, 
    0x914a, 0x9149, 0x9144, 0x9145, 0x9152, 0x9151, 0x9154, 0x9155, 
    0x94aa, 0x94a9, 0x94a4, 0x94a5, 0x9492, 0x9491, 0x9494, 0x9495, 
    0x944a, 0x9449, 0x9444, 0x9445, 0x9452, 0x9451, 0x9454, 0x9455, 
    0x952a, 0x9529, 0x9524, 0x9525, 0x9512, 0x9511, 0x9514, 0x9515, 
    0x954a, 0x9549, 0x9544, 0x9545, 0x9552, 0x9551, 0x9554, 0x9555, 
    0x4aaa, 0x4aa9, 0x4aa4, 0x4aa5, 0x4a92, 0x4a91, 0x4a94, 0x4a95, 
    0x4a4a, 0x4a49, 0x4a44, 0x4a45, 0x4a52, 0x4a51, 0x4a54, 0x4a55, 
    0x492a, 0x4929, 0x4924, 0x4925, 0x4912, 0x4911, 0x4914, 0x4915, 
    0x494a, 0x4949, 0x4944, 0x4945, 0x4952, 0x4951, 0x4954, 0x4955, 
    0x44aa, 0x44a9, 0x44a4, 0x44a5, 0x4492, 0x4491, 0x4494, 0x4495, 
    0x444a, 0x4449, 0x4444, 0x4445, 0x4452, 0x4451, 0x4454, 0x4455, 
    0x452a, 0x4529, 0x4524, 0x4525, 0x4512, 0x4511, 0x4514, 0x4515, 
    0x454a, 0x4549, 0x4544, 0x4545, 0x4552, 0x4551, 0x4554, 0x4555, 
    0x52aa, 0x52a9, 0x52a4, 0x52a5, 0x5292, 0x5291, 0x5294, 0x5295, 
    0x524a, 0x5249, 0x5244, 0x5245, 0x5252, 0x5251, 0x5254, 0x5255, 
    0x512a, 0x5129, 0x5124, 0x5125, 0x5112, 0x5111, 0x5114, 0x5115, 
    0x514a, 0x5149, 0x5144, 0x5145, 0x5152, 0x5151, 0x5154, 0x5155, 
    0x54aa, 0x54a9, 0x54a4, 0x54a5, 0x5492, 0x5491, 0x5494, 0x5495, 
    0x544a, 0x5449, 0x5444, 0x5445, 0x5452, 0x5451, 0x5454, 0x5455, 
    0x552a, 0x5529, 0x5524, 0x5525, 0x5512, 0x5511, 0x5514, 0x5515, 
    0x554a, 0x5549, 0x5544, 0x5545, 0x5552, 0x5551, 0x5554, 0x5555
};

uint8_t always_inline mfmtobin(uint16_t x)
{
    uint8_t y;
    x = be16toh(x) << 1;
    asm volatile (
        "lsrs %1,%1,#2 ; rrx %0,%0\n"
        "lsrs %1,%1,#2 ; rrx %0,%0\n"
        "lsrs %1,%1,#2 ; rrx %0,%0\n"
        "lsrs %1,%1,#2 ; rrx %0,%0\n"
        "lsrs %1,%1,#2 ; rrx %0,%0\n"
        "lsrs %1,%1,#2 ; rrx %0,%0\n"
        "lsrs %1,%1,#2 ; rrx %0,%0\n"
        "lsrs %1,%1,#2 ; rrx %0,%0\n"
        "rev %0,%0\n"
        : "=&r" (y) : "r" (x) );
    return y;
}

void mfm_to_bin(const void *in, void *out, unsigned int nr)
{
    const uint16_t *_in = in;
    uint8_t *_out = out;
    while (nr--)
        *_out++ = mfmtobin(*_in++);
}

void mfm_ring_to_bin(const uint16_t *ring, unsigned int mask,
                     unsigned int idx, void *out, unsigned int nr)
{
    unsigned int head;
    head = min_t(unsigned int, nr, mask+1-idx);
    mfm_to_bin(&ring[idx], out, head);
    if (head != nr) 
        mfm_to_bin(ring, (uint8_t *)out + head, nr - head);
}

uint16_t fm_sync(uint8_t dat, uint8_t clk)
{
    uint16_t _dat = mfmtab[dat] & 0x5555;
    uint16_t _clk = (mfmtab[clk] & 0x5555) << 1;
    return _clk | _dat;
}

uint16_t bc_rdata_flux(struct image *im, uint16_t *tbuf, uint16_t nr)
{
    uint32_t ticks_per_cell = im->ticks_per_cell;
    uint32_t ticks = im->ticks_since_flux;
    uint32_t x, y = 32, todo = nr;
    struct image_buf *bc = &im->bufs.read_bc;
    uint32_t *bc_b = bc->p, bc_c = bc->cons, bc_p = bc->prod & ~31;
    unsigned int bc_mask = (bc->len / 4) - 1;

    /* Convert pre-generated bitcells into flux timings. */
    while (bc_c != bc_p) {
        y = bc_c % 32;
        x = be32toh(bc_b[(bc_c / 32) & bc_mask]) << y;
        bc_c += 32 - y;
        im->cur_bc += 32 - y;
        im->cur_ticks += (32 - y) * ticks_per_cell;
        while (y < 32) {
            y++;
            ticks += ticks_per_cell;
            if ((int32_t)x < 0) {
                *tbuf++ = (ticks >> 4) - 1;
                ticks &= 15;
                if (!--todo)
                    goto out;
            }
            x <<= 1;
        }
    }

    ASSERT(y == 32);

out:
    bc->cons = bc_c - (32 - y);
    im->cur_bc -= 32 - y;
    im->cur_ticks -= (32 - y) * ticks_per_cell;
    im->ticks_since_flux = ticks;

    if (im->cur_bc >= im->tracklen_bc) {
        im->cur_bc -= im->tracklen_bc;
        ASSERT(im->cur_bc < im->tracklen_bc);
        im->tracklen_ticks = im->cur_ticks - im->cur_bc * ticks_per_cell;
        im->cur_ticks -= im->tracklen_ticks;
    }

    return nr - todo;
}

/*
 * Local variables:
 * mode: C
 * c-file-style: "Linux"
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: nil
 * End:
 */
