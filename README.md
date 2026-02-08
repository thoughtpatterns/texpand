# texpand

Convert LaTeX macros to Unicode characters on standard input. Whitespace is
trimmed from inputs.

## Installation

Requires `gperf`.

```bash
make -C ./src install
```

## Usage

```bash
printf %s '\\theta' | texpand
# θ

printf '\n %s \n' '\\theta' | texpand
# θ

printf %s '\\mathbb{Z}' | texpand
# ℤ
```

Macros which take an argument require `{}` around the argument. Subscripts and
superscripts are not supported; if this is unacceptable, see
[UnicodeIt](https://github.com/svenkreiss/unicodeit).

Text editors which can pipe to `sh` can use `texpand` on a keybind to expand
LaTeX macros. For Kakoune, the snippet

```bash
define-command texpand-word %{ evaluate-commands -draft -save-regs 'e|' -no-hooks %{
	set-register e 'nop'
	set-register | %{
		root="$(mktemp -d)" ; stdin="$root/stdin" ; stdout="$root/stdout"
		tee "$stdin" | texpand > "$stdout"

		if [ "$?" -eq 0 ]
		then cat "$stdout"
		else printf 'set-register e fail "%s"\n' "failed to expand macro" > "$kak_command_fifo" ; cat "$stdin"
		fi

		rm -rf "$root"
	}

	execute-keys 'h<a-f>\|<ret>'
	%reg{e}
}}

map global insert <c-t> '<a-;>: texpand-word<ret>'
```

will bind `<c-t>` in insert mode to a command, which,
1. selects to the last `\`,
2. passes the selection to `texpand`,
3. and replaces the selected word with the procured Unicode character if
   successful; else, does nothing, and prints an error message to `*debug*`.

For example, let `|` represent the cursor, so that our buffer is
```
\mu|
```
then `<c-t>` in insert mode will result in
```
μ|
```
but if the expansion were to fail (i.e., if the macro were invalid), the buffer
would instead be unchanged; e.g., let our buffer be
```
\abcde|
```
then `<c-t>` gives
```
\abcde|
```
and prints the message `"failed to expand macro"` on the status line.
