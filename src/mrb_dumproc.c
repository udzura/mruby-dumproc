/*
** mrb_dumproc.c - Dumproc class
**
** Copyright (c) Uchio Kondo 2016
**
** See Copyright Notice in LICENSE
*/

#include <stdio.h>
#include <stdlib.h>

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/error.h>
#include <mruby/compile.h>
#include <mruby/dump.h>
#include <mruby/proc.h>

#include "mrb_dumproc.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

static mrb_value mrb_dumproc_proc2mrb(mrb_state *mrb, mrb_value self)
{
  char *path;
  mrb_value proc_mrb;
  struct RProc *proc;
  int flags = DUMP_ENDIAN_LIL;
  mrb_get_args(mrb, "z&", &path, &proc_mrb);
  proc = mrb_proc_ptr(proc_mrb);

  FILE *wfp = fopen(path, "wb");
  if(wfp == NULL) {
    mrb_sys_fail(mrb, "fopen failed");
  }

  int n = mrb_dump_irep_binary(mrb, proc->body.irep, flags, wfp);
  if (n != MRB_DUMP_OK) {
    mrb_sys_fail(mrb, "fopen failed");
  }

  fclose(wfp);

  return mrb_fixnum_value(n);
}

static mrb_value mrb_dumproc_load(mrb_state *mrb, mrb_value self)
{
  char *path;
  FILE *infile;
  struct RProc *proc;

  mrb_get_args(mrb, "z", &path);
  infile = fopen(path, "rb");
  if(infile == NULL) {
    mrb_sys_fail(mrb, "fopen failed");
  }

  mrb_irep* irep = mrb_read_irep_file(mrb, infile);
  proc = mrb_proc_new(mrb, irep);

  mrb_value o = mrb_load_string(mrb, "Proc.new {}");
  //mrb_proc_copy(mrb_proc_ptr(o), proc);

  fclose(infile);
  return o;
}

void mrb_mruby_dumproc_gem_init(mrb_state *mrb)
{
  struct RClass *dumproc;
  dumproc = mrb_define_module(mrb, "Dumproc");
  mrb_define_module_function(mrb, dumproc, "proc2mrb", mrb_dumproc_proc2mrb, (MRB_ARGS_REQ(1)|MRB_ARGS_BLOCK()));
  mrb_define_module_function(mrb, dumproc, "load", mrb_dumproc_load, MRB_ARGS_REQ(1));
  DONE;
}

void mrb_mruby_dumproc_gem_final(mrb_state *mrb)
{
}
