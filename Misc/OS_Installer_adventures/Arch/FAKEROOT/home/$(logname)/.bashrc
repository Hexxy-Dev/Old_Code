# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# User specific environment
if ! [[ "$PATH" =~ "$HOME/.local/bin:$HOME/bin:" ]]
then
    PATH="$HOME/.local/bin:$HOME/bin:$PATH"
fi
export PATH


if ! [[ "$PATH" =~ "$HOME/bin/random:" ]]
then
    PATH="$HOME/bin/random:$PATH"
fi
export PATH

# Uncomment the following line if you don't like systemctl's auto-paging feature:
# export SYSTEMD_PAGER=

# User specific aliases and functions
if [ -d ~/.bashrc.d ]; then
	for rc in ~/.bashrc.d/*; do
		if [ -f "$rc" ]; then
			. "$rc"
		fi
	done
fi
unset rc

#infinite history
export HISTSIZE=20
export HISTFILESIZE=-1


alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias groups='groups $(logname)'

#TEMPORARY
alias vim='nvim'

#this is the actual prompt
PS1='[\u@\h \W]\$ '