bool    isspecial(char c)
{
    if (c != '[' && c != ']' && c != '\\' && c != '`' && c != '_' && c != '^' && c != '{' && c != '|' && c != '}')
        return (false);
    return (true);
}

bool    isforbidenuser(char c)
{
    if (c == '\0' || c == ' ' || c == '\r' || c == '\n' || c == '@')
        return (true);
    return (false);
}