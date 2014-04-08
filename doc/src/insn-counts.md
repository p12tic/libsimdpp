Instruction counts {#insn-counts}
==================

Many functions in the library do not map to single instruction. This makes hard
to evaluate the performance impact of the functions. To combat this issue,
_instruction counts_ are provided. An _instruction count_ is simply the number
of instructions that are used to implement specific function at the specific
vector width. The instructions are counted as follows:

 - Any register-register moves and copies that do not cross the processor
 execution domains are ignored.

 - General purpose domain instructions are ignored except when they move data
 to or from memory or one of the SIMD domains.

 - If the implementation of a function is dependent on template arguments (for
 example, element selector), then the instruction count is defined as a range
 with both lower and upper bounds.

 - If the function loads or computes static data, then the instruction count is
 defined as a range. The lower count calculated as if the loads from memory or
 computation didn't happen (for example, if the function was used in a small
 loop and there were enough registers to cache the data). The upper count is
 calculated as if the data needed to be recomputed each time.

If instruction count is not listed for specific architecture, then the function
directly maps to one instruction. This rule does not apply to the following
architectures:

`X86_FMA3`, `X86_FMA4` and `X86_XOP`.

For these, if instruction count is not listed, the instruction counts
should be interpreted as if the architecture is not supported.

Note, that instruction count is very, very imprecise way to measure
performance. It is provided just as a quick way to estimate how well specific
functionality maps to target architecture.
