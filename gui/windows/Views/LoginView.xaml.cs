﻿namespace PasswordManager
{
    /// <summary>
    /// Interaction logic for LoginView.xaml
    /// </summary>
    public partial class LoginView
    {
        #region Variables

        private readonly LoginViewModel _ViewModel;

        #endregion

        #region Ctor

        public LoginView()
            : this(false)
        {
        }
        public LoginView(bool twoFactor)
        {
            _ViewModel = new LoginViewModel(this, twoFactor);
            DataContext = _ViewModel;

            InitializeComponent();

            PasswordBox.Password = _ViewModel.Model.Password;
        }

        #endregion

        private void PasswordBox_PasswordChanged(object sender, System.Windows.RoutedEventArgs e)
        {
            System.Windows.Controls.PasswordBox passwordBox = (System.Windows.Controls.PasswordBox)sender;
            _ViewModel.OnPasswordChanged(passwordBox.Password);
        }
    }
}
