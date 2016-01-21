#include <u.h>
#include <lib.h>
#include "rcall.h"

#include <assert.h>

static uint8 testpkt[] = {
  0x00, 0x00, 0x00, 0x04, 0xfa, 0x31, 0x8d, 0x82, 0x49, 0x01, 0x2d, 0x14,
  0x50, 0x8b, 0xdb, 0xb9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void convR2M2R(Rcall *r, uint8 size);

int
main(int argc, char **argv)
{
	Rcall r;
	
	r.type = Trx;
	convR2M2R(&r, 1+1+2);
	assert(r.type == Trx);
	
	r.type = Ttx;
	r.preamblems = 10;
	memcpy(r.pkt, testpkt, sizeof testpkt);
	convR2M2R(&r, 1+1+2+Npkt);
	assert(r.type == Ttx);
	assert(r.preamblems == 10);
	assert(memcmp(r.pkt, testpkt, sizeof testpkt) == 0);
	
	r.type = Rrx;
	memcpy(r.pkt, testpkt, sizeof testpkt);
	convR2M2R(&r, 1+1+Npkt);
	assert(r.type == Rrx);
	assert(memcmp(r.pkt, testpkt, sizeof testpkt) == 0);
	
	r.type = Rerr;
	r.err = 123;
	convR2M2R(&r, 1+1+1);
	assert(r.type == Rerr);
	assert(r.err == 123);
	
	print("ok\n");
}

void
convR2M2R(Rcall *r, uint8 size)
{
	uint8 buf[RCALLMAX];

	assert(convR2M(r, buf, sizeof buf) == size);
	assert(convM2R(buf, sizeof buf, r) == size);
}

int
radiorpc(uint8 *buf)
{
	werrstr("not implemented");
	return -1;
}