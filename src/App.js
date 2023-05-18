import './App.css';
import { Routes, Route, HashRouter } from 'react-router-dom';
// import Home from './Pages/Home'
import ViewDataBase from './Pages/ViewDataBase';
import NoPage from './Pages/NoPage';
import axios from 'axios';
import Collections from './Pages/Collections';



function App() {


  return (
    <div className="App">
      <HashRouter>
        <Routes>
          <Route index element={<ViewDataBase />}/>
          <Route index element={<Collections />} />
          <Route path="/viewDataBase" element={<ViewDataBase />} />
          <Route path="/Collections" element={<Collections />} />
          <Route path="*" element={<NoPage />} />
        </Routes>
      </HashRouter>

    </div>
  );
}

export default App;
