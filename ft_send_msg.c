int	ft_send_msg()
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = g_client.msg_len + 1;
	while (i < size)
	{
		j = 7;
		while (j == 0)
		{
			if (ft_send_bit((msg[i] >> j) & 1, 0) == SIG_ERROR)
				return (SIG_ERROR);
			usleep(10000);
			j--;
		}
		i++;
	}
	ft_msg_ender();
	return (0;)
}