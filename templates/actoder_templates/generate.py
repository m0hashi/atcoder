<%!
    import shutil
    from logging import getLogger

    import onlinejudge_template.generator.python as python
    import onlinejudge_template.generator.about as about
    import onlinejudge_template.generator.hook as hook
%>\
<%
    logger = getLogger(__name__)
    if not shutil.which("yapf"):
        logger.warning("yapf is not installed. If you want to generate well-formatted code, please install it. You can use $ pip3 install yapf")
    else:
        format_config = "{" + ", ".join([
            "BASED_ON_STYLE: google",
            "COLUMN_LIMIT: 9999",
        ]) + "}"
        hook.register_filter_command(["yapf", "--style", format_config], data=data)
%>\
#!/usr/bin/env python3
# usage: $ oj generate-input 'python3 generate.py'
# usage: $ oj generate-input --hack-actual=./a.out --hack-expected=./naive 'python3 generate.py'
import random

# generated by ${about.title} ${about.version} (${about.url})
def main():
${python.generate_input(data)}
${python.write_input(data)}

if __name__ == "__main__":
    main()