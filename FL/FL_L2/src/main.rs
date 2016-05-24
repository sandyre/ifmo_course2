use std::io;

fn main()
{
    let mut success: u8 = 0;
    let mut curr_char_ind: usize = 0;
    let mut current_state: u16 = 0;
    let mut input_string = String::new();

    println!("This program tests input string to match a*b*((ac)?|ab) expression.");
    println!("Enter a string");

    io::stdin().read_line(&mut input_string)
        .expect("Failed to read the line");

    let mut inp_str_chars = input_string.chars();

    loop
    {
        let mut curr_char = inp_str_chars.next();
        match current_state
        {
            0 =>
            {
                match curr_char
                {
                    Some('a') =>
                    {
                        current_state = 1;
                    },

                    Some('b') =>
                    {
                        current_state = 2;
                    }

                    Some('\n') =>
                    {
                        success = 1;
                        break;
                    }

                    _ =>
                    {
                        success = 0;
                        break;
                    },
                }
            },

            1 =>
            {
                match curr_char
                {
                    Some('a') =>
                    {
                        current_state = 1;
                    },

                    Some('b') =>
                    {
                        current_state = 3;
                    },

                    Some('c') =>
                    {
                        current_state = 4;
                    }

                    Some('\n') =>
                    {
                        success = 1;
                        break;
                    }

                    _ =>
                    {
                        success = 0;
                        break;
                    },
                }
            },

            2 =>
            {
                match curr_char
                {
                    Some('a') =>
                    {
                        current_state = 5;
                    },

                    Some('b') =>
                    {
                        current_state = 2;
                    }

                    Some('\n') =>
                    {
                        success = 1;
                        break;
                    }

                    _ =>
                    {
                        success = 0;
                        break;
                    },
                }
            },

            3 =>
            {
                match curr_char
                {
                    Some('a') =>
                    {
                        current_state = 5;
                    },

                    Some('b') =>
                    {
                        current_state = 2;
                    }

                    Some('\n') =>
                    {
                        success = 1;
                        break;
                    }

                    _ =>
                    {
                        success = 0;
                        break;
                    },
                }
            },

            4 =>
            {
                match curr_char
                {
                    Some('\n') =>
                    {
                        success = 1;
                        break;
                    }

                    _ =>
                    {
                        success = 0;
                        break;
                    },
                }
            },

            5 =>
            {
                match curr_char
                {
                    Some('b') =>
                    {
                        current_state = 6;
                    },

                    Some('c') =>
                    {
                        current_state = 4;
                    }

                    Some('\n') =>
                    {
                        success = 1;
                        break;
                    }

                    _ =>
                    {
                        success = 0;
                        break;
                    },
                }
            },

            6 =>
            {
                match curr_char
                {
                    Some('\n') =>
                    {
                        success = 1;
                        break;
                    }

                    _ =>
                    {
                        success = 0;
                        break;
                    },
                }
            },

            _ =>
            {
                println!("Internal recognitor error.");
            },
        }
    }

    if success == 1
    {
        println!("String matches the pattern.");
    }
    else if success == 0
    {
        println!("String does not match the pattern.");
    }
}
