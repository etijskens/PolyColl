# -*- coding: utf-8 -*-

"""
Package polycoll
=======================================

Top-level package for polycoll.
"""

__version__ = "0.0.0"

try:
    import polycoll.core
except ModuleNotFoundError as e:
    # Try to build this binary extension:
    from pathlib import Path
    import click
    from et_micc2.project import auto_build_binary_extension
    msg = auto_build_binary_extension(Path(__file__).parent, 'core')
    if not msg:
        import polycoll.core
    else:
        click.secho(msg, fg='bright_red')


def hello(who='world'):
    """'Hello world' method.

    :param str who: whom to say hello to
    :returns: a string
    """
    result = "Hello " + who
    return result

# Your code here...